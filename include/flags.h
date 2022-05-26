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
    TF_CDOOR           = 1 << 6
} TileFlags;

typedef enum {
    EV_NONE            = 1 << 0,
    EV_QUIT            = 1 << 1,
    EV_MOVE            = 1 << 2,
    EV_OPEN            = 1 << 3,
    EV_CLOSE           = 1 << 4
} EventFlags;

typedef enum {
    TILE_FLOOR = 0,
    TILE_WALL,
    TILE_CDOOR,
    TILE_ODOOR,
    TILE_ROCK,
    TILE_WATER,
    NUM_TILES
} TileTypes;

#endif
