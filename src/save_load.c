/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022
* 
* This file is a part of Goblin Caves
*
* Goblin Caves is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Goblin Caves is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Goblin Caves.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <goblincaves.h>

/**************************
 * Tile save/load functions
 **************************/
void save_tile(Tile tile, FILE *f) {
    fwrite(&(tile.pos), sizeof(Vec2i),1,f);
    fwrite(&(tile.glyph), sizeof(Glyph),1,f);
    fwrite(&(tile.flags), sizeof(TileFlags),1,f);
}

Tile load_tile(FILE *f) {
    Tile result;
    fread(&(result.pos), sizeof(Vec2i),1,f);
    fread(&(result.glyph), sizeof(Glyph),1,f);
    fread(&(result.flags), sizeof(TileFlags),1,f);
    return result;
}

/*************************
 * Map save/load functions
 *************************/
void save_map(Map **headref, FILE *f) {
    /* Saves the ENTIRE map list, starting with head */
    int i;
    int count = 0;
    Map *last = *headref;
    while(last->next != NULL) {
        count++;
        last = last->next;
    }
    fwrite(&count, sizeof(int), 1,f);
    
    last = *headref;
    while(last != NULL) {
        fwrite(&(last->lvl), sizeof(int), 1, f);
        //remove_mlist_player(&(last->monsters));
        //cull_mlist(last->monsters);
        count = count_mlist(last->monsters);
        fwrite(&count, sizeof(int),1,f);
        for(i = 0; i < count; i++) {
            /* It shouldn't matter if the player is saved twice, as long as we
             * don't load the player twice! */
            write_log("Saving monster!");
            save_monster(last->monsters[i].data, f);
        }
        for(i = 0; i < (MAP_WIDTH * MAP_HEIGHT); i++) {
            save_tile(last->tiles[i], f);
        }
        last = last->next;
    }
    write_log("Map saved successfully!");
}

Map* load_map(FILE *f) {
    /* Reads an ENTIRE map list, and returns the head */
    Map* head = NULL;
    Map* readmap = NULL;
    Map* nextmap = NULL;
    Monster *monster = NULL;
    int count,mcount;
    int i = 0;
    int j = 0;
    fread(&count, sizeof(int),1,f);

    while(i <= count) {
        readmap = create_map(NULL);
        fread(&(readmap->lvl), sizeof(int), 1, f);
        fread(&mcount, sizeof(int),1,f);
        for(j = 0; j < mcount; j++){
            monster = load_monster(f);
            if(check_flag(monster->flags, MF_PLAYER)){
                write_log("Read player monster, skipping.");
                free(monster);
                monster = NULL;
            } else {
                /*Monster read is not player, add to list*/
                push_mlist(&(readmap->monsters), monster);
                //readmap->monsters = add_mlist_front(readmap->monsters, monster);
                write_log("Read monster, added to monster list!");
            }
        }
        for(j = 0; j < (MAP_WIDTH * MAP_HEIGHT); j++) {
            readmap->tiles[j] = load_tile(f);
        }
        if(head == NULL) {
            head = readmap;
        } else if (nextmap == NULL) {
            head->next = readmap;
            readmap->prev = head;
            nextmap = readmap;
        } else {
            nextmap->next = readmap;
            readmap->prev = nextmap;
            nextmap = readmap;
        }
        i++;
    }
    write_log("Map loaded successfully!");

    return head;
}

/****************************
 * Monster save/load functions
 ****************************/
void save_monster(Monster *monster, FILE *f) {
    if(!monster) {
        return;
    }
    int namesize = strlen(monster->name) + 1; /* add 1 for null terminator */
    fwrite(&namesize, sizeof(int), 1, f); fwrite(&(monster->name), sizeof(char), namesize, f); fwrite(&(monster->pos), sizeof(Vec2i), 1, f);
    fwrite(&(monster->dpos), sizeof(Vec2i), 1, f);
    fwrite(&(monster->glyph), sizeof(Glyph), 1, f);
    fwrite(&(monster->str), sizeof(int), 1, f);
    fwrite(&(monster->dex), sizeof(int), 1, f);
    fwrite(&(monster->vit), sizeof(int), 1, f);
    fwrite(&(monster->per), sizeof(int), 1, f);
    fwrite(&(monster->curhp), sizeof(int), 1, f);
    fwrite(&(monster->flags), sizeof(int), 1, f);
}

Monster* load_monster(FILE *f) {
    Monster *monster = create_monster();
    int namesize;
    char name[80] = "Loading: ";
    fread(&namesize, sizeof(int), 1, f);
    fread(&(monster->name), sizeof(char), namesize, f);
    strcat(name, monster->name);
    write_log(name);
    fread(&(monster->pos), sizeof(Vec2i), 1, f);
    fread(&(monster->dpos), sizeof(Vec2i), 1, f);
    fread(&(monster->glyph), sizeof(Glyph), 1, f);
    fread(&(monster->str), sizeof(int), 1, f);
    fread(&(monster->dex), sizeof(int), 1, f);
    fread(&(monster->vit), sizeof(int), 1, f);
    fread(&(monster->per), sizeof(int), 1, f);
    fread(&(monster->curhp), sizeof(int), 1, f);
    fread(&(monster->flags), sizeof(int), 1, f);
    return monster;
}

/********************************
 * Game save/load functions
 * The big mambajamba whammy bois
 * that do the thing
 ********************************/
int save_game(void) {
    /* Open file for writing, eventually save_game will take a filename as
     * input, possibly "$HOME/.goblincaves/" + the characters name + "_data.bin
     * or something cool like that. */
    FILE *f = fopen("save_data.bin","wb+");

    /* Write player */
    save_monster(g_player, f);

    /* Write Map */
    save_map(&g_maphead, f);

    /* Write current level int */
    fwrite(&(g_mapcur->lvl), sizeof(int), 1, f);

    /* Close file */
    fclose(f);

    return EV_CHST_MENU;
}

int load_game(void) {
    /* Open file for reading, eventually there will be a string passed in to
     * load_game with the names of the characters in "$HOME/.goblincaves/"*/
    FILE *f = fopen("save_data.bin","rb+");
    int curlvl;

    if(f == NULL) {
        error_msg_box("No save data found!", BLACK, WHITE);
        return EV_CHST_MENU;
    }

    /* Clear g_maphead, g_player */
    if(g_maphead != NULL) {
        destroy_map(&g_maphead);
    }
    if(g_player != NULL) {
        destroy_player();
    }

    /* read and set g_player */
    g_player = load_monster(f);

    /* Read map list and set g_maphead */
    g_maphead = load_map(f);

    /* read current level int curlvl*/
    fread(&(curlvl), sizeof(int), 1, f);

    /* set g_mapcur to curlvl */
    g_mapcur = find_map(g_maphead, curlvl);
    push_mlist(&(g_mapcur->monsters), g_player);

    /* set g_tilemap */
    g_tilemap = g_mapcur->tiles;

    /* Close file */
    fclose(f);

    /* Update FOV */
    update_fov();
    write_log("Saved game loaded successfully!");
    return EV_CHST_GAME;
}

