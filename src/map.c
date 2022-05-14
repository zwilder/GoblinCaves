#include <goblincaves.h>

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 48;
Tile* g_map;

/* Playing with this idea for tiles - sure makes it easy to grab some presets
 * real quick. The tile table should only be used for dungeon creation, not for
 * modifying individual tiles (eg a door being opened would NOT have its
 * definition changed by referencing the table, it would just toggle the
 * (BLOCKS_MOVEMENT | BLOCKS_LIGHT) flags */
typedef enum {
    TILE_FLOOR = 0,
    TILE_WALL,
    TILE_DOOR,
    NUM_TILES
} TileTypes;

Tile tileTable[NUM_TILES] = 
{
    /* char name[32], int x, int y, TileFlags, Glyph */
    {"floor", 0, 0, (NONE), {'.', WHITE, BLACK} },
    {"wall", 0, 0, (BLOCKS_MOVEMENT | BLOCKS_LIGHT), {'#', WHITE, BLACK} },
    {"door", 0, 0, (BLOCKS_MOVEMENT | BLOCKS_LIGHT | DOOR), {'+', BROWN, BLACK} }
};

Tile* create_map(void) {
    int i, x, y;
    Tile* newMap = calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(Tile));
    for(x = 0; i < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            i = get_map_index(x,y);
            newMap[i] = tileTable[TILE_FLOOR];
            newMap[i].pos.x = x;
            newMap[i].pos.y = y;
        }
    }

    return newMap;
}

int get_map_index(int x, int y) {
    return (x + (MAP_WIDTH * y));
}

void destroy_map(void) {
    if(NULL != g_map) {
        free(g_map);
    }
}
