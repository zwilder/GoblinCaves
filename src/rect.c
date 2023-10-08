/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022-2023
* 
* This file is a part of Goblin Caves
*
* Goblin Caves is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Goblin Caves is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Goblin Caves.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <goblincaves.h>

/* This file contains functions that make the Rect struct useful, including a
 * linked list, and will eventually be portable outside this project. Requires vec2i.h,
 * mt19937.h to be included. 
 */

/****************
 * Rect functions
 ****************/
Rect make_rect(int x, int y, int width, int height) {
    /* Given x,y coordinates and a width,height, return a Rect */
    Rect result;
    result.pos.x = x;
    result.pos.y = y;
    result.dim.x = width;
    result.dim.y = height;
    return result;
}

bool point_in_rect(Rect a, Vec2i b) {
    /* Given a rect and an x,y Vec2 point, return if the point is in the
     * rectangle */
    bool x = ((b.x > a.pos.x) && (b.x < a.dim.x));
    bool y = ((b.y > a.pos.y) && (b.y < a.dim.y));
    return (x && y);
}

bool xy_in_rect(Rect a, int x, int y) {
    /* Same as point_in_rect above, but the user passed in an x,y coordinate
     * pair */
    return(point_in_rect(a, make_vec(x,y)));
}

Vec2i random_point_in_rect(Rect a) {
    /* Return a Vec2i containing a random point in the rectangle */
    Vec2i result = make_vec(0,0);
    result.x = mt_rand(a.pos.x + 1, a.pos.x + a.dim.x - 1);
    result.y = mt_rand(a.pos.y + 1, a.pos.y + a.dim.y - 1);
    return result;
}

bool rect_intersect(Rect a, Rect b) {
    /* Check if two rectangles intersect, the math was wigging me out so all
     * credit for this goes to:
     * https://silentmatt.com/rectangle-intersection/
     */
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
    
    if((ax1 <= bx2) && (ax2 >= bx1) && (ay1 <= by2) && (ay2 >= by1)) {
        result = true;
    }

    return result; 
}

Vec2i get_center(Rect a) {
    /* Returns a Vec2i containing the x,y coordinates of the center of a given
     * Rect.
     */
    Vec2i result;
    result.x = a.pos.x + (int)(a.dim.x / 2);
    result.y = a.pos.y + (int)(a.dim.y / 2);
    return result;
}

/********************
 * RectList functions
 *
 * Simple linked list of Rects
 ********************/
RectList* create_RectList(Rect data) {
    /* Create and return a RectList node */
    RectList *node = malloc(sizeof(RectList));
    node->data = data;
    node->next = NULL;
    return node;
}

void push_RectList(RectList **headref, Rect data) {
    /* Add a RectList node to a list */
    RectList *node = create_RectList(data);
    if(!(*headref)) {
        *headref = node;
        return;
    }
    node->next = *headref;
    *headref = node;
}

Rect pop_RectList(RectList **headref) {
    /* Remove the head of the RectList list, returning the data Rect */
    if(!(*headref)) {
        return make_rect(0,0,0,0);
    }
    Rect data = (*headref)->data;
    RectList *tmp = *headref;
    *headref = (*headref)->next;
    free(tmp);
    return data;
}

int count_RectList(RectList *headref) {
    /* Count the number of nodes in a RectList */
    if(!headref) {
        return 0;
    }
    return (count_RectList(headref->next) + 1);
}

void destroy_RectList(RectList **headref) {
    /* Starting with a reference to the head node, go through and free the
     * entire RectList from memory */
    RectList *tmp = NULL;
    while(*headref) {
        tmp = *headref;
        *headref = (*headref)->next;
        free(tmp);
    }
}
