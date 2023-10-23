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
const int MAP_HEIGHT = 24;
const int MIN_ROOM_SIZE = 5;
const int MAX_ROOM_SIZE = 10;
const int MIN_NUM_ROOMS = 8;
const int MAX_NUM_ROOMS = 30;
const int MAX_MONSTERS = 4;
Map *g_maphead = NULL; /* Reference to map list head (level 0) */
Map *g_mapcur = NULL; /* Reference to current map */
Tile *g_tilemap = NULL; /* Reference to current tilemap */

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
    {{'_', BRIGHT_BLACK, BLACK}     , {0,0}, (TF_ALTAR)},
    {{' ', BRIGHT_BLACK, BLACK}     , {0,0}, (TF_BLK_MV)}
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

Map* find_map(Map *headref, int lvl) {
    Map *last = headref;
    while(last != NULL) {
        if(last->lvl == lvl) {
            return last;
        }
        last = last->next;
    }
    return headref;
}

void destroy_map(Map **map) {
    Map *ref;
    while((*map) != NULL) {
        ref = pop_map(map);
        if(ref->tiles) {
            destroy_tilemap(ref->tiles, ref->lvl);
        }
        if(ref) {
            free(ref);
        }
        ref = NULL;
    }
    *map = NULL;
}

Tile* create_tilemap(void) {
    int i;

    Tile tile = tileTable[TILE_DN];
    Tile *newMap = malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(Tile));
    for(i = 0; i < (MAP_WIDTH * MAP_HEIGHT); i++) {
        newMap[i] = tile;
    }
    return newMap;
}

void destroy_tilemap(Tile *tilemap, int lvl) {
    if(NULL != tilemap) {
        log_tilemap(tilemap, lvl);
        free(tilemap);
    }
    tilemap = NULL;
}

/**********************
 * Assistance functions
 **********************/
int get_map_index(int x, int y) {
    if(!in_bounds(x,y)) {
        return 0;
    }
    return (x * MAP_HEIGHT + y);
}

int get_map_index_vec(Vec2i vec) {
    return(get_map_index(vec.x,vec.y));
}

char get_glyphch_at(int x, int y) {
    if(!in_bounds(x,y)) {
        return ' ';
    }
    return g_tilemap[get_map_index(x,y)].glyph.ch;
}

char get_glyphch_at_vec(Vec2i vec) {
    return (get_glyphch_at(vec.x,vec.y));
}

int get_glyphbg_at(int x, int y) {
    if(!in_bounds(x,y)) {
        return BLACK;
    }
    return g_tilemap[get_map_index(x,y)].glyph.bg;
}

int get_glyphbg_at_vec(Vec2i vec) {
    return(get_glyphbg_at(vec.x,vec.y));
}

void set_glyphbg_at(int x, int y, Color color) {
    if(!in_bounds(x,y)) {
        return;
    }
    g_tilemap[get_map_index(x,y)].glyph.bg = color;
}

void set_glyphbg_at_vec(Vec2i vec, Color color) {
    set_glyphbg_at(vec.x,vec.y,color);
}

Glyph get_glyph_at(int x, int y) {
    if(!in_bounds(x,y)) {
        return (make_glyph(' ', BLACK, BLACK));
    }
    return g_tilemap[get_map_index(x,y)].glyph;
}

void set_glyphch_at(int x, int y, char ch) {
    if(!in_bounds(x,y)) {
        return;
    }
    g_tilemap[get_map_index(x,y)].glyph.ch = ch;
}

void set_glyphch_at_vec(Vec2i vec, char ch) {
    set_glyphch_at(vec.x,vec.y,ch);
}

void set_glyphfg_at(int x, int y, Color color) {
    if(!in_bounds(x,y)) return;
    g_tilemap[get_map_index(x,y)].glyph.fg = color;
}

void set_glyphfg_at_vec(Vec2i vec, Color color) {
    set_glyphfg_at(vec.x,vec.y,color);
}

int get_tflags_at(int x, int y) {
    if(!in_bounds(x,y)) {
        return TF_NONE;
    }
    return g_tilemap[get_map_index(x,y)].flags;
}

void remove_tflags_at(int x, int y, int flags) {
    if(!in_bounds(x,y)) {
        return;
    }
    set_tflags_at(x,y, remove_flag(get_tflags_at(x,y), flags));
}

void engage_tflags_at(int x, int y, int flags) {
    if(!in_bounds(x,y)) {
        return;
    }
    set_tflags_at(x,y, engage_flag(get_tflags_at(x,y), flags));
}

void engage_tflags_at_vec(Vec2i vec, int flags) {
    engage_tflags_at(vec.x,vec.y,flags);
}

void set_tflags_at(int x, int y, int mask) {
    if(!in_bounds(x,y)) {
        return;
    }
    g_tilemap[get_map_index(x,y)].flags = mask;
}

void set_tflags_at_vec(Vec2i vec, int mask) {
    set_tflags_at(vec.x,vec.y,mask);
}

bool check_tflags_at(int x, int y, int flags) {
    if(!in_bounds(x,y)) {
        return TF_NONE;
    }
    return (check_flag(get_tflags_at(x,y), flags));
}

int count_neighbors(Vec2i pos, char a) {
    if(!in_bounds(pos.x,pos.y)) {
        return 0;
    }
    int x,y;
    int count = 0;
    for(x = pos.x - 1; x < pos.x + 1; x++) {
        for(y = pos.y - 1; y < pos.y + 1; y++) {
            if(!eq_vec(make_vec(x,y), pos)) {
                if(get_glyphch_at(x,y) == a) {
                    count++;
                }
            }
        }
    }
    return count;
}

bool is_visible(int x, int y) {
    if(!in_bounds(x,y)) {
        return false;
    }
    return check_flag(g_tilemap[get_map_index(x,y)].flags, TF_VIS);
}

bool is_explored(int x, int y) {
    if(!in_bounds(x,y)) {
        return false;
    }
    return check_flag(g_tilemap[get_map_index(x,y)].flags, TF_EXP);
}

bool is_cdoor(int x, int y) {
    if(!in_bounds(x,y)) {
        return false;
    }
    return check_flag(g_tilemap[get_map_index(x,y)].flags, TF_CDOOR);
}

bool is_odoor(int x, int y) {
    if(!in_bounds(x,y)) {
        return false;
    }
    return check_flag(g_tilemap[get_map_index(x,y)].flags, TF_ODOOR);
}

bool is_blocked(int x, int y) {
    if(!in_bounds(x,y)) {
        return true;
    }
    return check_flag(g_tilemap[get_map_index(x,y)].flags, TF_BLK_MV);
}

void mark_explored(int x, int y) {
    if(!in_bounds(x,y)) {
        return;
    }
    g_tilemap[get_map_index(x,y)].flags =
        engage_flag(g_tilemap[get_map_index(x,y)].flags, TF_EXP);
}

void place_tile(Vec2i pos, int type) {
    if(!in_bounds(pos.x,pos.y)) {
        return;
    }
    int index = get_map_index(pos.x,pos.y);
    g_tilemap[index] = tileTable[type];
    g_tilemap[index].pos.x = pos.x;
    g_tilemap[index].pos.y = pos.y;
}

Vec2i find_down_stairs(void) {
    int x,y;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            if(get_glyphch_at(x,y) == '>') {
                return make_vec(x,y);
            }
        }
    }
    return make_vec(0,0);
}

Vec2i find_up_stairs(void) {
    int x,y;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            if(get_glyphch_at(x,y) == '<') {
                return make_vec(x,y);
            }
        }
    }
    return make_vec(0,0);
}

void tile_flavor_msg(Vec2i pos) {
    if(check_tflags_at(pos.x,pos.y, TF_WATER)) {
        if(mt_chance(10)) {
            push_msg(&g_msghead, "Water sloshes around your feet.");
        } else if(mt_chance(10)) {
            push_msg(&g_msghead, "*SQUISH*");
        } else if(mt_chance(5)) {
            push_msg(&g_msghead, "A small fish darts between your boots.");
        }
    }
    if(check_tflags_at(pos.x,pos.y, TF_ALTAR)) {
        if(mt_chance(10)) {
            push_msg(&g_msghead, "Bones crunch under your feet.");
        }
        push_msg(&g_msghead, "You stand next to a crude, blood stained, altar.");
    }
    if(check_tflags_at(pos.x,pos.y, TF_UP)) {
        push_msg(&g_msghead, 
                "You see a primative staircase leading upward.");
    }
    if(check_tflags_at(pos.x,pos.y, TF_DN)) {
        push_msg(&g_msghead, 
                "You see a crude stair leading downward.");
    }
    if(check_tflags_at(pos.x,pos.y, TF_ODOOR)) {
        if(mt_chance(10)) {
            push_msg(&g_msghead, "This doorway is carved with obscene symbols.");
        } else if(mt_chance(10)) {
            push_msg(&g_msghead, "You notice claw marks on the door.");
        } /*else {
            push_msg(&g_msghead, 
                    "You pass through a rough doorway.");
        }*/
    }
    if((count_neighbors(pos, '0') > 0)) {
        if(mt_chance(10)) {
            push_msg(&g_msghead, 
                    "The tall pillars near you cast sinister shadows on the dungeon floor.");
        } else if(mt_chance(5)) {
            push_msg(&g_msghead, "Something darts around a pillar at the corner of your eye!");
            /* Spawn goblin out of sight lol */
        }
    }
}

bool in_bounds(int x, int y) {
    if((x < 0) || (x > MAP_WIDTH)) {
        return false; 
    }
    if((y < 0) || (y > MAP_HEIGHT)) {
        return false;
    }
    return true;
}
