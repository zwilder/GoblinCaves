#ifndef RECT_H
#define RECT_H

typedef struct {
    Vec2i dim;
    Vec2i pos;
} Rect;

/******************
 * rect.c functions
 ******************/
Rect make_rect(int x, int y, int width, int height); 
bool point_in_rect(Rect a, Vec2i b);
bool rect_intersect(Rect a, Rect b);
Vec2i get_center(Rect a);

#endif
