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

struct Node {
    Rect data;
    struct Node* leftChild;
    struct Node* rightChild;
};

typedef struct Node Node;

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

/***********************
 * Major data structures
 ***********************/
/* Major Goal: Five (major) data types - structured like: Player, Enemy, Tile,
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
extern Tile* g_map;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern const int MIN_ROOM_SIZE;
extern const int MAX_ROOM_SIZE;
extern const int MIN_NUM_ROOMS;
extern const int MAX_NUM_ROOMS;

/******************
 * tree.c functions
 ******************/
Node* new_node(Rect data);
void make_bsp_dungeon(void); 
void make_rooms_in_leaves(Node *node);
void connect_leaves(Node *node);
int count_leaves(Node *node);
bool split_node(Node *node);
void split_tree(Node *node);
void destroy_node(Node* node);

/*******************
 * vec2i.c functions
 *******************/
Vec2i make_vec(int x, int y);
Vec2i add_vec(Vec2i a, Vec2i b);
Vec2i subtract_vec(Vec2i a, Vec2i b);

/******************
 * rect.c functions
 ******************/
Rect make_rect(int x, int y, int width, int height); 
bool point_in_rect(Rect a, Vec2i b);
bool rect_intersect(Rect a, Rect b);
Vec2i get_center(Rect a);

/***************************
 * curses_engine.c functions
 ***************************/
bool curses_setup(void);
void setcolor(int fg, int bg);
void unsetcolor(int fg, int bg);
void curses_draw(int x, int y, Glyph glyph);
void msg_box(char* msg, Color fg, Color bg);
bool yn_prompt(char* msg, Color fg, Color bg);
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
bool mt_bool(void); 
bool mt_chance(int chance);

/***************************
 * handle_events.c functions
 ***************************/
int handle_keyboard(int input);
Vec2i get_direction(char* action_str);

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
void destroy_screen(Glyph *screen);
void clear_screen(Glyph *screen);
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
void place_tile(Vec2i pos, int type);
int get_map_index(int x, int y);
bool point_in_rect(Rect a, Vec2i b);
bool rect_intersect(Rect a, Rect b);
Vec2i get_center(Rect a);
void draw_dungeon(void);
void place_room(Rect room);
void place_htunnel(int x1, int x2, int y);
void place_vtunnel(int y1, int y2, int x);
void place_orthogonal_tunnel(Vec2i a, Vec2i b);
void place_corridor(Vec2i a, Vec2i b); 
void make_basic_dungeon(void);
void place_doors(Rect room);
int count_neighbors(Vec2i pos, char a);
char get_glyph_at(int x, int y);
void place_border(void);
void destroy_map(void);

/*****************
 * log.c functions 
 *****************/
void start_log(void);
void write_log(char *msg);
void log_map(void);
void log_time(void);
void log_vec(Vec2i a);
void log_rect(Rect a);
void log_leaves(Node *node);

#endif
