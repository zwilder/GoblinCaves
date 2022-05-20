#include <goblincaves.h>

/* These are temporarily set to the screen size while I take a sanity break from
 * getting the camera/rendering sorted, bad things will happen if the const
 * SCREEN_WIDTH and SCREEN_HEIGHT do not equal exactly MAP_WIDTH and MAP_HEIGHT. */
const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 80;
Tile* g_map;

/* Playing with this idea for tiles - sure makes it easy to grab some presets
 * real quick. The tile table should only be used for dungeon creation, not for
 * modifying individual tiles (eg a door being opened would NOT have its
 * definition changed by referencing the table, it would just toggle the
 * (BLOCKS_MOVEMENT | BLOCKS_LIGHT) flags */
typedef enum {
    TILE_FLOOR = 0,
    TILE_WALL,
    TILE_CDOOR,
    TILE_ODOOR,
    TILE_ROCK,
    TILE_WATER,
    NUM_TILES
} TileTypes;

Tile tileTable[NUM_TILES] = 
{
    /* Glyph                        , Vec2i, TileFlags */
    {{'.', WHITE, BLACK}            , {0,0}, (TF_NONE)},
    {{'#', WHITE, BLACK}            , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'+', BROWN, BLACK}            , {0,0}, (TF_BLK_MV | TF_BLK_LT | TF_CDOOR)},
    {{'/', BROWN, BLACK}            , {0,0}, (TF_ODOOR)},
    {{'*', BRIGHT_BLACK, BROWN}     , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'~', BRIGHT_CYAN, BLUE}       , {0,0}, (TF_BLK_MV)}
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

int get_map_index(int x, int y) {
    return (x + (MAP_WIDTH * y));
}

bool point_in_rect(Rect a, Vec2i b) {
    bool x = ((b.x > a.pos.x) && (b.x < a.dim.x));
    bool y = ((b.y > a.pos.y) && (b.y < a.dim.y));
    return (x && y);
}

bool rect_intersect(Rect a, Rect b) {
    /* https://silentmatt.com/rectangle-intersection/ */
    int ax1,ay1,ax2,ay2;
    int bx1,by1,bx2,by2;
    bool result = false;

    ax1 = a.pos.x;
    ay1 = a.pos.y;
    ax2 = ax1 + a.dim.x;
    ay2 = ay1 + a.dim.y;
    bx1 = b.pos.x;
    by1 = b.pos.y;
    bx2 = bx1 + b.dim.x;
    by2 = by1 + b.dim.y;
    
    if((ax1 < bx2) && (ax2 > bx1) && (ay1 < by2) && (ay2 > by1)) {
        result = true;
    }

    return result; 
}

Vec2i get_center(Rect a) {
    Vec2i result;
    result.x = a.pos.x + (int)(a.dim.x / 2);
    result.y = a.pos.y + (int)(a.dim.y / 2);
    return result;
}

void draw_dungeon(void) {
    /* Simple hardcoded two rooms, procedural generation t'later */
    int x, y, i;
    Rect newRoom;
    /* Fill with rock */
    /*
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            i = get_map_index(x,y);
            g_map[i] = tileTable[TILE_ROCK];
            g_map[i].pos.x = x;
            g_map[i].pos.y = y;
        }
    }
    */
    place_border();
    /* Place rooms */
    /*
    newRoom.pos.x = 1;
    newRoom.pos.y = 1;
    newRoom.dim.x = 15;
    newRoom.dim.y = 15;
    place_room(newRoom);
    */

    newRoom.pos.x = 16;
    newRoom.pos.y = 10;
    newRoom.dim.x = 17;
    newRoom.dim.y = 12;
    place_room(newRoom);

    /* Connect rooms */
    g_map[get_map_index(16,13)] = tileTable[TILE_CDOOR];
    g_map[get_map_index(16,13)].pos.x = 16;
    g_map[get_map_index(16,13)].pos.x = 13;

    /* Place stairs */
    /* Place player */
    g_player->pos = get_center(newRoom);
    /* Place enemies */
    /* Place pickups */
}

void place_room(Rect room) {
    int x, y, i;
    for(x = room.pos.x; x <= room.pos.x + room.dim.x; x++){
        for(y=room.pos.y; y <= room.pos.y + room.dim.y; y++) {
            i = get_map_index(x,y);
            if(room.pos.x == x 
                   || room.pos.y == y
                   || room.dim.x + room.pos.x == x 
                   || room.dim.y + room.pos.y == y) {
                g_map[i] = tileTable[TILE_WALL];
            } else {
                g_map[i] = tileTable[TILE_FLOOR];
            }
            g_map[i].pos.x = x;
            g_map[i].pos.y = y;
        }
    }
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

void destroy_map(void) {
    if(NULL != g_map) {
        free(g_map);
    }
}
