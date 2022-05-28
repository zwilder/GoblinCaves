#ifndef MAP_FEATURES_H
#define MAP_FEATURES_H

/*******************
 * Feature placement
 *******************/
void place_room(Rect room);
void place_altar(Rect room);
void place_marsh(Rect room);
void place_pillars(Rect Room);
void round_room(Rect room);
void place_htunnel(int x1, int x2, int y);
void place_vtunnel(int y1, int y2, int x);
void place_orthogonal_tunnel(Vec2i a, Vec2i b);
void place_corridor(Vec2i a, Vec2i b); 
void place_hdoor(int x, int y);
void place_vdoor(int x, int y);
void place_doors(Rect room);
void place_border(void);

#endif
