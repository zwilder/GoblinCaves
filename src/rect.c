#include <goblincaves.h>

bool point_in_rect(Rect a, Vec2i b) {
    bool x = ((b.x > a.pos.x) && (b.x < a.dim.x));
    bool y = ((b.y > a.pos.y) && (b.y < a.dim.y));
    return (x && y);
}

bool rect_intersect(Rect a, Rect b) {
    /* https://silentmatt.com/rectangle-intersection/ */
    int ax1,ay1,ax2,ay2;
    int bx1,by1,bx2,by2;
    bool result = false;

    ax1 = a.pos.x;
    ay1 = a.pos.y;
    ax2 = ax1 + a.dim.x;
    ay2 = ay1 + a.dim.y;
    bx1 = b.pos.x;
    by1 = b.pos.y;
    bx2 = bx1 + b.dim.x;
    by2 = by1 + b.dim.y;
    
    if((ax1 < bx2) && (ax2 > bx1) && (ay1 < by2) && (ay2 > by1)) {
        result = true;
    }

    return result; 
}

Vec2i get_center(Rect a) {
    Vec2i result;
    result.x = a.pos.x + (int)(a.dim.x / 2);
    result.y = a.pos.y + (int)(a.dim.y / 2);
    return result;
}

