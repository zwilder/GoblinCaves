#include <goblincaves.h>

Vec2i make_vec(int x, int y) {
    Vec2i result;
    result.x = x;
    result.y = y;
    return result;
}
Vec2i add_vec(Vec2i a, Vec2i b) {
    Vec2i result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vec2i subtract_vec(Vec2i a, Vec2i b) {
    Vec2i result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}
