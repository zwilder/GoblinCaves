#ifndef GOBLINCAVES_H
#define GOBLINCAVES_H

/*
 * This file will be chonky for a minute, likely that I will split it up into
 * multiple header files once I get the basic framework established.
 */

/**********
 * Includes
 **********/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include <color.h>

/***********************
 * Minor data structures
 ***********************/
typedef struct {
    int x;
    int y;
} Vec2i;

typedef struct {
    char ch;
    Color fg;
    Color bg;
} Glyph;

typedef struct {
    Vec2i dim;
    Vec2i pos;
} Rect;

typedef enum {
    NONE            = 1 << 0,
    VISIBLE         = 1 << 1,
    BLOCKS_MOVEMENT = 1 << 2,
    EXPLORED        = 1 << 3,
    BLOCKS_LIGHT    = 1 << 4,
    DOOR            = 1 << 5
} TileFlags;

/***********************
 * Major data structures
 ***********************/
/* Major Goal: Five (major) data types - structured like Angband: Player, Enemy, Tile,
Effect, Pickup. */
typedef struct { 
    Vec2i pos;
    Glyph glyph;
} Player;

typedef struct {
    char name[32];
    Vec2i pos;
    TileFlags flags;
    Glyph glyph;
} Tile;

/*********
 * Externs
 *********/
extern Player* g_player;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern Glyph* g_screen;
extern Tile* g_map;
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

/***************************
 * curses_engine.c functions
 ***************************/
bool curses_setup(void);
void setcolor(int fg, int bg);
void unsetcolor(int fg, int bg);
void curses_draw(void);
void msg_box(char* msg, Color fg, Color bg);
void curses_close(void);

/*************************
 * game_engine.c functions
 *************************/
void engine_init(void);
void engine_run(void);
void engine_close(void);

/***************************
 * handle_events.c functions
 ***************************/
int handle_keyboard(int input);

/********************
 * update.c functions
 ********************/
/* Game logic functions */

/******************
 * draw.c functions
 ******************/
Glyph* create_screen(void);
void draw_screen(void);
void destroy_screen(void);
void clear_screen(void);
int get_screen_index(int x, int y);

/********************
 * player.c functions
 ********************/
Player* create_player(Vec2i pos);
void destroy_player(void);

/*****************
 * map.c functions
 *****************/
Tile* create_map(void);
int get_map_index(int x, int y);
void destroy_map(void);

#endif
