/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022
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

Vec2iList* bh_line(Vec2i start, Vec2i finish) {
    Vec2iList *results = NULL;
    int e,j,i;
    int dX = abs(start.x - finish.x);
    int dY = abs(start.y - finish.y);

    if(dX >= dY)
    {
        e = dY - dX; // [e]rror
        j = start.y;

        if(start.x < finish.x)
        {
            // Octants 1,2
            for(i = start.x; i <= finish.x; ++i)
            {
                bh_line_add(&results, make_vec(i,j));
                if((e >= 0) && (finish.y >= start.y))
                {
                    // 1
                    j += 1;
                    e -= dX;
                }
                else if((e >= 0) && (finish.y < start.y))
                {
                    // 2
                    j -= 1;
                    e -= dX;
                }
                e += dY;
            }
        }
        else if(start.x > finish.x)
        {
            // Octants 5,6
            for(i = start.x; i >= finish.x; --i)
            {
                bh_line_add(&results, make_vec(i, j));
                if((e >= 0) && (finish.y >= start.y))
                {
                    // 6
                    j += 1;
                    e -= dX;
                }
                else if((e >= 0) && (finish.y < start.y))
                {
                    // 5
                    j -= 1;
                    e -= dX;
                }
                e += dY;
            }
        }
    }
    else if (dX < dY)
    {
        e = dX - dY; // [e]rror
        i = start.x;
        if(start.y < finish.y)
        {
            // Octants 7,8
            for(j = start.y; j <= finish.y; ++j)
            {
                bh_line_add(&results, make_vec(i,j));
                if((e >= 0) && (finish.x >= start.x))
                {
                    // 8
                    i += 1;
                    e -= dY;
                }
                else if((e >= 0) && (finish.x < start.x))
                {
                    // 7
                    i -= 1;
                    e -= dY;
                }
                e += dX;
            }
        }
        else if(start.y > finish.y)
        {
            // Octants 3,4
            for(j = start.y; j >= finish.y; --j)
            {
                bh_line_add(&results, make_vec(i,j));
                if((e >= 0) && (finish.x >= start.x))
                {
                    // 3
                    i += 1;
                    e -= dY;
                }
                else if((e >= 0) && (finish.x < start.x))
                {
                    // 4
                    i -= 1;
                    e -= dY;
                }
                e += dX;
            }
        }
    }

    return results;
}

void bh_line_add(Vec2iList **head, Vec2i pos) {
    if(!vec2i_list_contains(*head, pos)) {
        push_vec2i_list(head, pos);
    }
}

Vec2iList* open_neighbors_at(Vec2i pos, bool checkMonsters) {
    Vec2iList *results = NULL;
    int x, y;
    for(x = pos.x - 1; x <= pos.x + 1; x++) {
        for(y = pos.y - 1; y <= pos.y + 1; y++) {
            if(!is_blocked(x,y) && in_bounds(x,y)) {
                if(!checkMonsters) {
                    push_vec2i_list(&results, make_vec(x,y));
                } else {
                    if(!monster_at_pos(g_mlist, make_vec(x,y), g_mapcur->lvl)) {
                        push_vec2i_list(&results, make_vec(x,y));
                    }
                }
            }
        }
    }
    return results;
}

/* ALl I need to make the following functions work in a test program is a
 * modified open_neighbors_at(pos) function, then vec2i.h/c. Might be worthwhile
 * once I get the last couple functions up making a nice NCurses demo of these,
 * maybe mimicing the RedBlobGames demos? */
Vec2iList * breadth_first_search(Vec2i start) {
    /* Breadth first search, returns ALL tiles that are not blocked.
     * Could be used for flood filling or other fun? Mostly here for comparison
     * in the future. */
    Vec2iList *reached = create_vec2i_list(start);
    Vec2iList *frontier = create_vec2i_list(start);
    Vec2iList *neighbors = NULL;
    int count = 0;
    int i = 0;
    Vec2i cur = make_vec(-1,-1);

    while(frontier) {
        cur = pop_vec2i_list(&frontier);
        neighbors = open_neighbors_at(cur, false);
        count = count_vec2i_list(neighbors);
        for(i = 0; i < count; i++) {
            if(!vec2i_list_contains(reached, neighbors[i].item)) {
                push_vec2i_list(&reached, neighbors[i].item);
                push_vec2i_list(&frontier, neighbors[i].item);
            }
        }
        destroy_vec2i_list(&neighbors);
        neighbors = NULL;
    }

    destroy_vec2i_list(&frontier);
    destroy_vec2i_list(&neighbors);
    return reached;
}

Vec2iHT* bfs_path(Vec2i start, Vec2i goal) {
    /* BFS with early exit, that returns a path from start to goal */
    Vec2iList *frontier = create_vec2i_list(start);
    Vec2iList *neighbors = NULL;
    Vec2iHT *camefrom = create_Vec2iHT(5000); 
    int count = 0;
    int i = 0;
    Vec2i cur = make_vec(-1,-1);
    Vec2i next = make_vec(-1,-1);
    Vec2i nullvec = make_vec(-1,-1);

    while(frontier) {
        cur = pop_vec2i_list(&frontier);
        if(eq_vec(cur, goal)) {
            /* Early exit, found goal */
            break;
        }
        neighbors = open_neighbors_at(cur, false);
        count = count_vec2i_list(neighbors);
        for(i = 0; i < count; i++) {
            next = neighbors[i].item;
            if(!eq_vec(search_Vec2iHT(camefrom, next),nullvec)) {
                push_vec2i_list(&frontier, next);
                insert_Vec2iHT(camefrom, next, cur);
            }
        }
        destroy_vec2i_list(&neighbors);
        neighbors = NULL;
    }
    destroy_vec2i_list(&frontier);
    destroy_vec2i_list(&neighbors);
    return camefrom;
}

