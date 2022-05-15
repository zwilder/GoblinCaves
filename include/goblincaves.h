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
#include <math.h>

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
    TF_NONE            = 1 << 0,
    TF_VIS             = 1 << 1,
    TF_BLK_MV          = 1 << 2,
    TF_EXP             = 1 << 3,
    TF_BLK_LT          = 1 << 4,
    TF_DOOR            = 1 << 5
} TileFlags;

/***********************
 * Major data structures
 ***********************/
/* Major Goal: Five (major) data types - structured like Angband: Player, Enemy, Tile,
Effect, Pickup. */
typedef struct { 
    Vec2i pos;
    Glyph glyph;
    int fovRadius;
} Player;

typedef struct {
    Glyph glyph;
    Vec2i pos;
    TileFlags flags;
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
 * fov.c functions
 *****************/
void fov(void);
void calculate_fov(float x, float y);

/*****************
 * map.c functions
 *****************/
Tile* create_map(void);
int get_map_index(int x, int y);
bool point_in_rect(Rect a, Vec2i b);
bool rect_intersect(Rect a, Rect b);
Vec2i get_center(Rect a);
void draw_dungeon(void);
void place_room(Rect room);
void place_border(void);
void destroy_map(void);

#endif
