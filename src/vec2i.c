#include <goblincaves.h>

Vec2i sum_vec(Vec2i a, Vec2i b) {
    Vec2i result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}
