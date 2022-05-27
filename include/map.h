#ifndef MAP_H
#define MAP_H

typedef struct {
    Glyph glyph;
    Vec2i pos;
    TileFlags flags;
} Tile;

/*****************
 * map.c functions
 *****************/

/**************************
 * Map creation/destruction
 **************************/
Tile* create_map(void);
void destroy_map(void);

/**********************
 * Assistance functions
 **********************/
int get_map_index(int x, int y);
char get_glyph_at(int x, int y);
int count_neighbors(Vec2i pos, char a);

/*******************
 * Feature placement
 *******************/
void place_tile(Vec2i pos, int type);
void place_room(Rect room);
void place_htunnel(int x1, int x2, int y);
void place_vtunnel(int y1, int y2, int x);
void place_orthogonal_tunnel(Vec2i a, Vec2i b);
void place_corridor(Vec2i a, Vec2i b); 
void place_hdoor(int x, int y);
void place_vdoor(int x, int y);
void place_doors(Rect room);
void place_border(void);

/******************
 * Dungeon creation
 ******************/
void draw_dungeon(void);
void make_basic_dungeon(void);

#endif
