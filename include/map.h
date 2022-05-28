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
void place_tile(Vec2i pos, int type);

#endif
