#include <goblincaves.h>

const int MAP_WIDTH = 79;
const int MAP_HEIGHT = 23;
Tile* g_map;

/* Playing with this idea for tiles - sure makes it easy to grab some presets
 * real quick. The tile table should only be used for dungeon creation, not for
 * modifying individual tiles (eg a door being opened would NOT have its
 * definition changed by referencing the table, it would just toggle the
 * (BLOCKS_MOVEMENT | BLOCKS_LIGHT) flags */

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

void place_tile(Vec2i pos, int type) {
    int index = get_map_index(pos.x,pos.y);
    g_map[index] = tileTable[type];
    g_map[index].pos.x = pos.x;
    g_map[index].pos.y = pos.y;
}

Tile* create_map(void) {
    int i, x, y;

    Tile tile = tileTable[TILE_FLOOR];
    Tile* newMap = calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(Tile));
    for(i = 0; i < (MAP_WIDTH * MAP_HEIGHT); i++) {
        newMap[i] = tile;
    }
    return newMap;
}

int get_map_index(int x, int y) {
    return (x + (MAP_WIDTH * y));
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
    place_tile(make_vec(16,13), TILE_CDOOR);

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
            if(room.pos.x == x 
                   || room.pos.y == y
                   || room.dim.x + room.pos.x == x 
                   || room.dim.y + room.pos.y == y) {
                place_tile(make_vec(x,y), TILE_WALL);
            } else {
                place_tile(make_vec(x,y), TILE_FLOOR);
            }
        }
    }
}

void place_corridor(Vec2i a, Vec2i b) {
    /* Orthogonal walk, courtesy of RedBlobGames
     * https://www.redblobgames.com/grids/line-drawing.html */
    int dx, dy, nx, ny, signx, signy, ix, iy, index;
    dx = a.x - b.x;
    dy = a.y - b.y;
    nx = abs(dx);
    ny = abs(dy);
    signx = dx > 0 ? 1 : -1;
    signy = dy > 0 ? 1 : -1;
    Vec2i p = make_vec(a.x,a.y);
    ix = 0;
    iy = 0;
    while(ix < nx || iy < ny) {
        if(((0.5 + ix) / nx) < ((0.5 + iy) /ny)) {
            /* Horizontal step */
            p.x += signx;
            ix++;
        } else {
            /* Vertical step */
            p.y += signy;
            iy++;
        }
        place_tile(p,TILE_FLOOR);
    }
}

void place_border(void) {
    int i, x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        place_tile(make_vec(x,0), TILE_ROCK);
        place_tile(make_vec(x, MAP_HEIGHT - 1), TILE_ROCK);
    }
    for(y = 0; y < MAP_HEIGHT; y++) {
        place_tile(make_vec(0,y), TILE_ROCK);
        place_tile(make_vec(MAP_WIDTH - 1, y), TILE_ROCK);
    }
}

void destroy_map(void) {
    if(NULL != g_map) {
        free(g_map);
    }
}
