#ifndef DRAW_H
#define DRAW_H

/******************
 * draw.c functions
 ******************/
Glyph* create_screen(void);
Vec2i get_camera(void);
void draw_screen(void);
void destroy_screen(Glyph *screen);
void clear_screen(Glyph *screen);
int get_screen_index(int x, int y);

#endif
