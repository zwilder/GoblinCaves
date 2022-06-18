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
    if(!Vec2i_list_contains(*head, pos)) {
        push_Vec2i_list(head, pos);
    }
}

Vec2iList* open_neighbors_at(Vec2i pos, bool checkMonsters) {
    Vec2iList *results = NULL;
    int x, y;
    Vec2i tl,tr,bl,br;
    // Diagonal
    tl = make_vec(pos.x - 1, pos.y - 1);
    tr = make_vec(pos.x + 1, pos.y - 1);
    bl = make_vec(pos.x - 1, pos.y + 1);
    br = make_vec(pos.x + 1, pos.y + 1);
    if(!is_blocked(tl.x,tl.y) && in_bounds(tl.x,tl.y)){
        if(!checkMonsters) {
            push_Vec2i_list(&results, tl);
        } else {
            if(!monster_at_pos(g_mlist, tl, g_mapcur->lvl)) {
                push_Vec2i_list(&results, tl);
            }
        }
    }
    if(!is_blocked(tr.x,tr.y) && in_bounds(tr.x,tr.y)){
        if(!checkMonsters) {
            push_Vec2i_list(&results, tr);
        } else {
            if(!monster_at_pos(g_mlist, tr, g_mapcur->lvl)) {
                push_Vec2i_list(&results, tr);
            }
        }
    }
    if(!is_blocked(bl.x,bl.y) && in_bounds(bl.x,bl.y)){
        if(!checkMonsters) {
            push_Vec2i_list(&results, bl);
        } else {
            if(!monster_at_pos(g_mlist, bl, g_mapcur->lvl)) {
                push_Vec2i_list(&results, bl);
            }
        }
    }
    if(!is_blocked(br.x,br.y) && in_bounds(br.x,br.y)){
        if(!checkMonsters) {
            push_Vec2i_list(&results, br);
        } else {
            if(!monster_at_pos(g_mlist, br, g_mapcur->lvl)) {
                push_Vec2i_list(&results, br);
            }
        }
    }
               
    // Cardinal
    for(x = pos.x - 1, y = pos.y; x <= pos.x + 1; x += 2) {
        if(!is_blocked(x,y) && in_bounds(x,y)) {
            if(!checkMonsters) {
                push_Vec2i_list(&results, make_vec(x,y));
            } else {
                if(!monster_at_pos(g_mlist, make_vec(x,y), g_mapcur->lvl)) {
                    push_Vec2i_list(&results, make_vec(x,y));
                }
            }
        }
    }
    for(y = pos.y - 1, x = pos.x; y <= pos.y + 1; y += 2) {
        if(!is_blocked(x,y) && in_bounds(x,y)) {
            if(!checkMonsters) {
                push_Vec2i_list(&results, make_vec(x,y));
            } else {
                if(!monster_at_pos(g_mlist, make_vec(x,y), g_mapcur->lvl)) {
                    push_Vec2i_list(&results, make_vec(x,y));
                }
            }
        }
    }
    /*
    // All the cordinates except center. I **think** adding the diagonals to the
    // list first (so they are at the back of the list) makes the paths slightly
    // smoother (more priority given to the things searched first?)
    for(x = pos.x - 1; x <= pos.x + 1; x++) {
        for(y = pos.y - 1; y <= pos.y + 1; y++) {
            if(!is_blocked(x,y) && in_bounds(x,y)) {
                if(!checkMonsters) {
                    push_Vec2i_list(&results, make_vec(x,y));
                } else {
                    if(!monster_at_pos(g_mlist, make_vec(x,y), g_mapcur->lvl)) {
                        push_Vec2i_list(&results, make_vec(x,y));
                    }
                }
            }
        }
    }
    */
    return results;
}

int movement_cost_at(Vec2i pos) {
    /*Stupid function, will eventually do something */
    return 0;
}

Vec2iHT* dijkstra_map(Vec2i start, bool monsterblock) {
    Vec2iPQ *frontier = create_Vec2iPQ(start, 0);
    Vec2iList *neighbors = NULL;
    Vec2iList *tmp = NULL;
    Vec2iHT *camefrom = create_Vec2iHT(5000); 
    Vec2iHT *costSoFar = create_Vec2iHT(5000); 
    Vec2i cost;

    int p = 0;
    int newcost = 0;
    Vec2i cur = NULLVEC;
    Vec2i next = NULLVEC;

    insert_Vec2iHT(camefrom, start, start);
    /* The cost is stored in the x of the value, y is 0 */
    /* If we pass this in, we should be able to get D maps for multiple things
     * by combining maps */
    insert_Vec2iHT(costSoFar, start, make_vec(0,0));
    while(frontier) {
        cur = pop_Vec2iPQ(&frontier);
        neighbors = open_neighbors_at(cur, monsterblock);
        for(tmp = neighbors; tmp; tmp = tmp->next) {
            next = tmp->item;
            cost = search_Vec2iHT(costSoFar, cur);
            newcost = cost.x + movement_cost_at(next);
            cost = search_Vec2iHT(costSoFar, next);
            if(vec_null(search_Vec2iHT(costSoFar, next)) || 
                    (newcost < cost.x)) {
                insert_Vec2iHT(costSoFar, next, make_vec(newcost, 0));
                p = newcost;
                push_Vec2iPQ(&frontier, next, p);
                insert_Vec2iHT(camefrom, next, cur);
            }
        }
        destroy_Vec2i_list(&neighbors);
        neighbors = NULL;
    }
    destroy_Vec2iPQ(&frontier);
    destroy_Vec2i_list(&neighbors);
    destroy_Vec2iHT(camefrom);
    return costSoFar;
}

Vec2i astar_step(Vec2i start, Vec2i goal, bool monsterblock) {
    Vec2iList *path = astar_path(start, goal, monsterblock);
    Vec2i result = start;
    if(path) {
        result = path->item;
    }
    destroy_Vec2i_list(&path);
    return result;
}

Vec2iList* construct_path(Vec2iHT *input, Vec2i start, Vec2i goal) {
    Vec2iList *path = NULL;
    Vec2i cur = goal;
    while(!eq_vec(cur, start)) {
        push_Vec2i_list(&path, cur);
        cur = search_Vec2iHT(input, cur);
    }
    return path;
}

Vec2iList* astar_path(Vec2i start, Vec2i goal, bool monsterblock) {
    Vec2iPQ *frontier = create_Vec2iPQ(start, 0);
    Vec2iList *neighbors = NULL;
    Vec2iList *tmp = NULL;
    Vec2iHT *camefrom = create_Vec2iHT(5000); 
    Vec2iHT *costSoFar = create_Vec2iHT(5000); 
    Vec2i cost;

    int p = 0;
    int newcost = 0;
    Vec2i cur = NULLVEC;
    Vec2i next = NULLVEC;

    insert_Vec2iHT(camefrom, start, start);
    /* The cost is stored in the x of the value, y is 0 */
    insert_Vec2iHT(costSoFar, start, make_vec(0,0));
    while(frontier) {
        cur = pop_Vec2iPQ(&frontier);
        if(eq_vec(cur, goal)) {
            /* Early exit, found goal */
            break;
        }
        neighbors = open_neighbors_at(cur, monsterblock);
        for(tmp = neighbors; tmp; tmp = tmp->next) {
            next = tmp->item;
            cost = search_Vec2iHT(costSoFar, cur);
            newcost = cost.x + movement_cost_at(next);
            cost = search_Vec2iHT(costSoFar, next);
            if(vec_null(search_Vec2iHT(costSoFar, next)) || 
                    (newcost < cost.x)) {
                insert_Vec2iHT(costSoFar, next, make_vec(newcost, 0));
                p = newcost + man_dist(goal,next);
                push_Vec2iPQ(&frontier, next, p);
                insert_Vec2iHT(camefrom, next, cur);
            }
        }
        destroy_Vec2i_list(&neighbors);
        neighbors = NULL;
    }
    tmp = construct_path(camefrom, start, goal);
    destroy_Vec2iPQ(&frontier);
    destroy_Vec2i_list(&neighbors);
    destroy_Vec2iHT(costSoFar);
    destroy_Vec2iHT(camefrom);
    return tmp;
}

