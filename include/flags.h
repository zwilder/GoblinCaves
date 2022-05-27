#ifndef FLAGS_H
#define FLAGS_H

/*******
 * Flags
 *******/

typedef enum {
    TF_NONE            = 1 << 0,
    TF_VIS             = 1 << 1,
    TF_BLK_MV          = 1 << 2,
    TF_EXP             = 1 << 3,
    TF_BLK_LT          = 1 << 4,
    TF_ODOOR           = 1 << 5,
    TF_CDOOR           = 1 << 6,
    TF_UP              = 1 << 7,
    TF_DN              = 1 << 8
} TileFlags;

typedef enum {
    EV_NONE            = 1 << 0,
    EV_QUIT            = 1 << 1,
    EV_MOVE            = 1 << 2,
    EV_OPEN            = 1 << 3,
    EV_CLOSE           = 1 << 4,
    EV_DN              = 1 << 5,
    EV_UP              = 1 << 6
} EventFlags;

typedef enum {
    TILE_FLOOR = 0,
    TILE_WALL,
    TILE_CDOOR,
    TILE_ODOOR,
    TILE_ROCK,
    TILE_WATER,
    TILE_UP,
    TILE_DN,
    NUM_TILES
} TileTypes;

bool check_flag(int mask, int flag);
int toggle_flag(int mask, int flag);
int remove_flag(int mask, int flag);
int engage_flag(int mask, int flag);

#endif
