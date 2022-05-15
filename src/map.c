#include <goblincaves.h>

/* These are temporarily set to the screen size while I take a sanity break from
 * getting the camera/rendering sorted, bad things will happen if the const
 * SCREEN_WIDTH and SCREEN_HEIGHT do not equal exactly MAP_WIDTH and MAP_HEIGHT. */
const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 24;
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
    TILE_ROCK,
    NUM_TILES
} TileTypes;

Tile tileTable[NUM_TILES] = 
{
    /* Glyph                        , Vec2i, TileFlags */
    {{'.', WHITE, BLACK}            , {0,0}, (TF_NONE)},
    {{'#', WHITE, BLACK}            , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'+', BROWN, BLACK}            , {0,0}, (TF_BLK_MV | TF_BLK_LT | TF_DOOR)},
    {{'*', BRIGHT_BLACK, BROWN}     , {0,0}, (TF_BLK_MV | TF_BLK_LT)}
};

Tile* create_map(void) {
    int i, x, y;

    Tile tile = tileTable[TILE_FLOOR];
    Tile* newMap = calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(Tile));
    for(i = 0; i < (MAP_WIDTH * MAP_HEIGHT); i++) {
        newMap[i] = tile;
    }

    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            i = get_map_index(x,y);
            tile.pos.x = x;
            tile.pos.y = y;
        }
    }
    return newMap;
}

void draw_dungeon(void) {
    place_border();
    /* Fill with rock */
    /* Place rooms */
    /* Connect rooms */
    /* Draw border */
    /* Place stairs */
    /* Place player */
    /* Place enemies */
    /* Place pickups */
}

void place_border(void) {
    int i, x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        i = get_map_index(x,0);
        g_map[i] = tileTable[TILE_ROCK];
        g_map[i].pos.x = x;
        g_map[i].pos.y = 0;
        i = get_map_index(x,MAP_HEIGHT - 1);
        g_map[i] = tileTable[TILE_ROCK];
        g_map[i].pos.x = x;
        g_map[i].pos.y = MAP_HEIGHT - 1;
    }
    for(y = 0; y < MAP_HEIGHT; y++) {
        i = get_map_index(0,y);
        g_map[i] = tileTable[TILE_ROCK];
        g_map[i].pos.x = 0;
        g_map[i].pos.y = y;
        i = get_map_index(MAP_WIDTH - 1, y);
        g_map[i] = tileTable[TILE_ROCK];
        g_map[i].pos.x = MAP_WIDTH - 1;
        g_map[i].pos.y = y;
    }
}

int get_map_index(int x, int y) {
    return (x + (MAP_WIDTH * y));
}

bool point_in_rect(Rect a, Vec2i b) {
    bool x = ((b.x > a.pos.x) && (b.x < a.dim.x));
    bool y = ((b.y > a.pos.y) && (b.y < a.dim.y));
    return (x && y);
}

void destroy_map(void) {
    if(NULL != g_map) {
        free(g_map);
    }
}
