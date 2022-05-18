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
#include <time.h>
#include <mt19937.h>

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
/***********************
 * Major data structures
 ***********************/
/* Major Goal: Five (major) data types - structured like Angband: Player, Enemy, Tile,
Effect, Pickup. */
typedef struct { 
    Vec2i pos;
    Vec2i dpos;
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

/*******************
 * vec2i.c functions
 *******************/
Vec2i sum_vec(Vec2i a, Vec2i b);

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
int get_input(void);
bool check_flag(int mask, int flag);
int toggle_flag(int mask, int flag);
int remove_flag(int mask, int flag);
int engage_flag(int mask, int flag);
int mt_rand(int min, int max); 
bool mt_bool(); 

/***************************
 * handle_events.c functions
 ***************************/
int handle_keyboard(int input);
Vec2i get_direction();

/********************
 * update.c functions
 ********************/
int update(int events);
void player_move(void);
void open_door(Vec2i pos);
void close_door(Vec2i pos);

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
void update_fov(void);
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
