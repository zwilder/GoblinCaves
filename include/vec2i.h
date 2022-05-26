#ifndef VEC2I_H
#define VEC2I_H

typedef struct {
    int x;
    int y;
} Vec2i;

/*******************
 * vec2i.c functions
 *******************/
Vec2i make_vec(int x, int y);
Vec2i add_vec(Vec2i a, Vec2i b);
Vec2i subtract_vec(Vec2i a, Vec2i b);

#endif
