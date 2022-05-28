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

/*
 * map.h MIGHT eventually be chonky, and better split into
 * the following files and related .c files
 * dungeon.h - Dungeon building functions
 *             (eg draw_dungeon(), make_basic_dungeon())
 * features.h - feature placement functions
 * map.h - map specific functions (eg get_map_index(), is_explored())
 * glyph.h - glyph specific functions (eg get_glyph_at() and relatives)
 */

/**************************
 * Map creation/destruction
 **************************/
Tile* create_map(void);
void destroy_map(void);

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

/*******************
 * Feature placement
 *******************/
void place_tile(Vec2i pos, int type);
void place_room(Rect room);
void place_altar(Rect room);
void place_marsh(Rect room);
void place_pillars(Rect Room);
void round_room(Rect room);
void place_htunnel(int x1, int x2, int y);
void place_vtunnel(int y1, int y2, int x);
void place_orthogonal_tunnel(Vec2i a, Vec2i b);
void place_corridor(Vec2i a, Vec2i b); 
void place_hdoor(int x, int y);
void place_vdoor(int x, int y);
void place_doors(Rect room);
void place_border(void);

/******************
 * Dungeon creation
 ******************/
void draw_dungeon(void);
void make_basic_dungeon(void);

#endif
