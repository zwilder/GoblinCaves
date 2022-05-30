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
#ifndef MAP_H
#define MAP_H

typedef struct {
    Glyph glyph;
    Vec2i pos;
    TileFlags flags;
} Tile;

struct Map {
    /* Note: Map is a double linked list */
    Tile *tiles;
    int lvl;
    struct Map *prev;
    struct Map *next;
};

typedef struct Map Map;

typedef enum {
    TILE_FLOOR = 0,
    TILE_WALL,
    TILE_CDOOR,
    TILE_ODOOR,
    TILE_ROCK,
    TILE_WATER,
    TILE_UP,
    TILE_DN,
    TILE_PILLAR,
    TILE_SHRUB,
    TILE_GRASS,
    TILE_PLANT,
    TILE_TREE,
    TILE_ALTAR,
    NUM_TILES
} TileTypes;


/*****************
 * map.c functions
 *****************/

/**************************
 * Map creation/destruction
 **************************/
Map* create_map(Tile *tilemap);
void append_map(Map **headref, Tile *tilemap);
Map* pop_map(Map **headref);
void destroy_map(Map **map); 

Tile* create_tilemap(void);
void destroy_tilemap(Tile *tilemap, int lvl);

/**********************
 * Assistance functions
 **********************/
int get_map_index(int x, int y);
char get_glyphch_at(int x, int y);
Glyph get_glyph_at(int x, int y);
void set_glyphch_at(int x, int y, char ch);
int get_glyphbg_at(int x, int y);
int get_tflags_at(int x, int y);
void set_tflags_at(int x, int y, int mask); 
void remove_tflags_at(int x, int y, int flags);
void engage_tflags_at(int x, int y, int flags);
bool check_tflags_at(int x, int y, int flags);
bool is_visible(int x, int y);
bool is_explored(int x, int y);
void mark_explored(int x, int y);
int count_neighbors(Vec2i pos, char a);
void place_tile(Vec2i pos, int type);
Vec2i find_down_stairs(void);
Vec2i find_up_stairs(void);

#endif
