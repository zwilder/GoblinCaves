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

Vec2i make_vec(int x, int y) {
    Vec2i result = {};
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

bool eq_vec(Vec2i a, Vec2i b) {
    return ((a.x == b.x) && (a.y == b.y));
}

int man_dist(Vec2i a, Vec2i b) {
    return (abs(a.x - b.x) + abs(a.y - b.y));
}

Vec2iList* create_vec2i_list(Vec2i pos) {
    Vec2iList *newnode = malloc(sizeof(Vec2iList));
    newnode->pos = pos;
    newnode->next = NULL;
    return newnode;
}

void push_vec2i_list(Vec2iList **head, Vec2i pos) {
    if(!(*head)) {
        *head = create_vec2i_list(pos);
        return;
    }
    Vec2iList *newnode = create_vec2i_list(pos);
    newnode->next = *head;
    *head = newnode;
}

Vec2i pop_vec2i_list(Vec2iList **head) {
    if(!(*head)) {
        return (make_vec(-1,-1));
    }
    Vec2iList *tmp = *head;
    *head = (*head)->next;
    Vec2i result = tmp->pos;
    free(tmp);
    return result;
}

int count_vec2i_list(Vec2iList *head) {
    if(!head) {
        return 0;
    }
    return (count_vec2i_list(head->next) + 1);
}

void destroy_vec2i_list(Vec2iList **head) {
    if(!(*head)) {
        return;
    }
    Vec2iList *tmp = NULL;
    while(*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

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

bool vec2i_list_contains(Vec2iList *head, Vec2i pos) {
    bool result = false;
    Vec2iList *tmp = head;
    while(tmp) {
        if(eq_vec(tmp->pos, pos)) {
            result = true;
            break;
        }
        tmp = tmp->next;
    }
    return result;
}
