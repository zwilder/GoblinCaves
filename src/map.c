#include <goblincaves.h>

const int MAP_WIDTH = 79;
const int MAP_HEIGHT = 23;
const int MIN_ROOM_SIZE = 5;
const int MAX_ROOM_SIZE = 10;
const int MIN_NUM_ROOMS = 8;
const int MAX_NUM_ROOMS = 30;
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
    {{'*', BRIGHT_BLACK, BLACK}     , {0,0}, (TF_BLK_MV | TF_BLK_LT)},
    {{'~', BRIGHT_CYAN, BLUE}       , {0,0}, (TF_BLK_MV)},
    {{'<', WHITE, BLACK}            , {0,0}, (TF_UP)},
    {{'>', WHITE, BLACK}            , {0,0}, (TF_DN)}
};

/**************************
 * Map creation/destruction
 **************************/
Tile* create_map(void) {
    int i, x, y;

    Tile tile = tileTable[TILE_FLOOR];
    Tile* newMap = calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(Tile));
    for(i = 0; i < (MAP_WIDTH * MAP_HEIGHT); i++) {
        newMap[i] = tile;
    }
    return newMap;
}

void destroy_map(void) {
    int x,y;
    if(NULL != g_map) {
        log_map();
        free(g_map);
    }
}

/**********************
 * Assistance functions
 **********************/
int get_map_index(int x, int y) {
    return (x * MAP_HEIGHT + y);
}

char get_glyph_at(int x, int y) {
    return g_map[get_map_index(x,y)].glyph.ch;
}

int count_neighbors(Vec2i pos, char a) {
    int x,y;
    int count = 0;
    for(x = pos.x - 1; x < pos.x + 1; x++) {
        for(y = pos.y - 1; y < pos.y + 1; y++) {
            if(get_glyph_at(x,y) == a) {
                count++;
            }
        }
    }
    return count;
}

/*******************
 * Feature placement
 *******************/
void place_tile(Vec2i pos, int type) {
    int index = get_map_index(pos.x,pos.y);
    g_map[index] = tileTable[type];
    g_map[index].pos.x = pos.x;
    g_map[index].pos.y = pos.y;
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

void place_htunnel(int x1, int x2, int y) {
    int i;
    int min = (x1 < x2 ? x1 : x2);
    int max = (x1 > x2 ? x1 : x2);
    for(i = min; i <= max; ++i)
    {
        place_tile(make_vec(i,y), TILE_FLOOR);
    }
}

void place_vtunnel(int y1, int y2, int x) {
    int i;
    int min = (y1 < y2 ? y1 : y2);
    int max = (y1 > y2 ? y1 : y2);
    for(i = min; i <= max; ++i)
    {
        place_tile(make_vec(x,i), TILE_FLOOR);
    }
}

void place_orthogonal_tunnel(Vec2i a, Vec2i b) {
    /* Orthogonal walk, courtesy of RedBlobGames
     * https://www.redblobgames.com/grids/line-drawing.html */

    /* I think this is broken? */
    int dx, dy, nx, ny, signx, signy, ix, iy;
    Vec2i p;
    dx = a.x - b.x;
    dy = a.y - b.y;
    nx = abs(dx);
    ny = abs(dy);
    signx = dx > 0 ? 1 : -1;
    signy = dy > 0 ? 1 : -1;
    p = make_vec(b.x,b.y);
    ix = 0;
    iy = 0;
    while(ix < nx || iy < ny) {
        /*if(((0.5 + ix) / nx) < ((0.5 + iy) /ny)) { */
        if(((1 + 2*ix) * ny) < ((1 + 2*iy) * nx)) {
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

void place_corridor(Vec2i a, Vec2i b) {
    if(mt_bool()) {
        place_htunnel(b.x, a.x, b.y);
        place_vtunnel(b.y, a.y, a.x);
    } else if (mt_bool()) {
        place_vtunnel(b.y, a.y, b.x);
        place_htunnel(b.x, a.x, a.y);
    } else {
        place_orthogonal_tunnel(a,b);
    }
}

void place_hdoor(int x, int y) {
    if(get_glyph_at(x,y) == '.' &&
            get_glyph_at(x - 1, y) == '#' &&
            get_glyph_at(x + 1, y) == '#' &&
            get_glyph_at(x, y - 1) != '+' &&
            get_glyph_at(x, y - 1) != '/' &&
            get_glyph_at(x, y + 1) != '+' &&
            get_glyph_at(x, y + 1) != '/') {
        place_tile(make_vec(x,y), (mt_chance(20) ? TILE_CDOOR : TILE_ODOOR));
    }
}

void place_vdoor(int x, int y) {
    if(get_glyph_at(x,y) == '.' &&
            get_glyph_at(x, y - 1) == '#' &&
            get_glyph_at(x, y + 1) == '#' &&
            get_glyph_at(x - 1, y) != '+' &&
            get_glyph_at(x - 1, y) != '/' &&
            get_glyph_at(x + 1, y) != '+' &&
            get_glyph_at(x + 1, y) != '/') {
        place_tile(make_vec(x,y), (mt_chance(20) ? TILE_CDOOR : TILE_ODOOR));
    }
}

void place_doors(Rect room) {
    int x,y;
    Vec2i pos;
    for(x = room.pos.x; x < room.pos.x + room.dim.x; x++) {
        place_hdoor(x,room.pos.y);
        place_hdoor(x, room.pos.y + room.dim.y);
    }
    for(y = room.pos.y; y < room.pos.y + room.dim.y; y++) {
        place_vdoor(room.pos.x, y);
        place_vdoor(room.pos.x + room.dim.x, y);
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

/******************
 * Dungeon creation
 ******************/
void draw_dungeon(void) {
    int x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            place_tile(make_vec(x,y), TILE_WALL);
        }
    }
    place_border();

    make_basic_dungeon();
}

void make_basic_dungeon(void) {
    int x,y,w,h,i;
    Rect newRoom;
    bool intersects;
    int numRooms = 0;
    int attempts = 0;
    Rect rooms[MAX_NUM_ROOMS];

    for(i = 0; i < MAX_NUM_ROOMS; i++) {
        rooms[i] = make_rect(-5,-5,0,0);
    }
    while(numRooms < MIN_NUM_ROOMS) {
        while(numRooms < MAX_NUM_ROOMS && attempts < 500) {
            x = mt_rand(1, MAP_WIDTH - MAX_ROOM_SIZE - 1);
            y = mt_rand(1, MAP_HEIGHT - MAX_ROOM_SIZE - 1);
            w = mt_rand(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
            h = mt_rand(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
            while(x % 2 != 0) {
                x = mt_rand(1, MAP_WIDTH - 1);
            }
            while(y % 2 != 0) {
                y = mt_rand(1, MAP_HEIGHT - 1);
            }
            newRoom = make_rect(x,y,w,h);
            intersects = false;
            for(i = 0; i < MAX_NUM_ROOMS; i++) {
               if(rect_intersect(newRoom, rooms[i])) {
                    intersects = true;
                    break;
               } 
            }
            if((newRoom.pos.x + newRoom.dim.x >= MAP_WIDTH) ||
                   (newRoom.pos.y + newRoom.dim.y >= MAP_HEIGHT)) {
                intersects = true;
            }
            if(!intersects) {
                place_room(newRoom);
                rooms[numRooms] = newRoom;
                numRooms += 1;
            }
            attempts++;
        }
    }

    for(i = 0; i < MAX_NUM_ROOMS; i++) {
        if(rooms[i].pos.x < 0) {
            break;
        }
        if(i > 0) {
            place_corridor(get_center(rooms[i]), get_center(rooms[i-1]));
        }
    }
    for(i = 0; i < MAX_NUM_ROOMS; i++) {
        if(rooms[i].pos.x < 0) {
            i--; /* i is now the number of the last room */
            break;
        }
        place_doors(rooms[i]);
    }

    place_tile(get_center(rooms[mt_rand(0,i-1)]), TILE_DN);
    place_tile(get_center(rooms[i]), TILE_UP);
    g_player->pos = get_center(rooms[i]); 
}

