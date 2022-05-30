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

/* Map width/height are one less than screen width/height, which "disables" the
 * map scrolling... at least until the UI is added then there really isnt any
 * point in this.
 */
const int MAP_WIDTH = 79;
const int MAP_HEIGHT = 23;
const int MIN_ROOM_SIZE = 5;
const int MAX_ROOM_SIZE = 10;
const int MIN_NUM_ROOMS = 8;
const int MAX_NUM_ROOMS = 30;
Tile* g_map;

Tile tileTable[NUM_TILES] = 
{
    /* Glyph                        , Vec2i, TileFlags */
    {{'.', WHITE, BLACK}            , {0,0}, (TF_NONE)},
    {{'#', BROWN, BLACK}            , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'+', BLACK, BROWN}            , {0,0}, (TF_BLK_MV | TF_BLK_LT | TF_CDOOR)},
    {{'/', BROWN, BLACK}            , {0,0}, (TF_ODOOR)},
    {{'*', BRIGHT_BLACK, BLACK}     , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'~', BRIGHT_CYAN, BLUE}       , {0,0}, (TF_WATER)},
    {{'<', WHITE, BLACK}            , {0,0}, (TF_UP)},
    {{'>', WHITE, BLACK}            , {0,0}, (TF_DN)},
    {{'0', WHITE, BLACK}            , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'\"', GREEN, BLACK}           , {0,0}, (TF_NONE)},
    {{'\'', BRIGHT_GREEN, BLACK}    , {0,0}, (TF_NONE)},
    {{';', GREEN, BLACK}            , {0,0}, (TF_NONE)},
    {{'T', GREEN, BLACK}            , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'_', BRIGHT_BLACK, BLACK}     , {0,0}, (TF_ALTAR)}

};

/**************************
 * Map creation/destruction
 **************************/
Map* create_map(Tile *tilemap) {
    if(NULL == tilemap) {
        tilemap = create_tilemap();
    }
    Map *newMap = malloc(sizeof(Map));
    newMap->tiles = tilemap;
    newMap->lvl = 0;
    newMap->next = NULL;
    newMap->prev = NULL;
    return newMap;
}

void append_map(Map **headref, Tile *tilemap) {
    Map *newMap = create_map(tilemap);
    Map *last = *headref;

    newMap->next = NULL;

    if(*headref == NULL) {
        newMap->prev = NULL;
        *headref = newMap;
        return;
    }
    while(last->next != NULL) {
        last = last->next;
    }

    newMap->lvl = last->lvl + 1;
    last->next = newMap;
    newMap->prev = last;
}

Map* pop_map(Map **headref) {
    Map *poppedLink = *headref;
    *headref = (*headref)->next;
    return poppedLink;
}

void destroy_map(Map **map) {
    Map *ref;
    while((*map) != NULL) {
        ref = pop_map(map);
        destroy_tilemap(ref->tiles);
        free(ref);
    }
}

Tile* create_tilemap(void) {
    int i, x, y;

    Tile tile = tileTable[TILE_FLOOR];
    Tile *newMap = malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(Tile));
    for(i = 0; i < (MAP_WIDTH * MAP_HEIGHT); i++) {
        newMap[i] = tile;
    }
    return newMap;
}

void destroy_tilemap(Tile *tilemap) {
    int x,y;
    if(NULL != tilemap) {
        log_tilemap(tilemap);
        free(tilemap);
    }
}

/**********************
 * Assistance functions
 **********************/
int get_map_index(int x, int y) {
    return (x * MAP_HEIGHT + y);
}

char get_glyphch_at(int x, int y) {
    return g_map[get_map_index(x,y)].glyph.ch;
}

int get_glyphbg_at(int x, int y) {
    return g_map[get_map_index(x,y)].glyph.bg;
}

Glyph get_glyph_at(int x, int y) {
    return g_map[get_map_index(x,y)].glyph;
}

void set_glyphch_at(int x, int y, char ch) {
    g_map[get_map_index(x,y)].glyph.ch = ch;
}

int get_tflags_at(int x, int y) {
    return g_map[get_map_index(x,y)].flags;
}

void remove_tflags_at(int x, int y, int flags) {
    set_tflags_at(x,y, remove_flag(get_tflags_at(x,y), flags));
}

void engage_tflags_at(int x, int y, int flags) {
    set_tflags_at(x,y, engage_flag(get_tflags_at(x,y), flags));
}

void set_tflags_at(int x, int y, int mask) {
    g_map[get_map_index(x,y)].flags = mask;
}

bool check_tflags_at(int x, int y, int flags) {
    return (check_flag(get_tflags_at(x,y), flags));
}

int count_neighbors(Vec2i pos, char a) {
    int x,y;
    int count = 0;
    for(x = pos.x - 1; x < pos.x + 1; x++) {
        for(y = pos.y - 1; y < pos.y + 1; y++) {
            if(x != pos.x && y != pos.y){
                if(get_glyphch_at(x,y) == a) {
                    count++;
                }
            }
        }
    }
    return count;
}

bool is_visible(int x, int y) {
    return check_flag(g_map[get_map_index(x,y)].flags, TF_VIS);
}

bool is_explored(int x, int y) {
    return check_flag(g_map[get_map_index(x,y)].flags, TF_EXP);
}

void mark_explored(int x, int y) {
    g_map[get_map_index(x,y)].flags =
        engage_flag(g_map[get_map_index(x,y)].flags, TF_EXP);
}

void place_tile(Vec2i pos, int type) {
    int index = get_map_index(pos.x,pos.y);
    g_map[index] = tileTable[type];
    g_map[index].pos.x = pos.x;
    g_map[index].pos.y = pos.y;
}

