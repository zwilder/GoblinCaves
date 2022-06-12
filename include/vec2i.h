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
#ifndef VEC2I_H
#define VEC2I_H

typedef struct {
    int x;
    int y;
} Vec2i;

struct Vec2iList {
    Vec2i pos;
    struct Vec2iList *next;
};

typedef struct Vec2iList Vec2iList;

/*******************
 * vec2i.c functions
 *******************/
Vec2i make_vec(int x, int y);
Vec2i add_vec(Vec2i a, Vec2i b);
Vec2i subtract_vec(Vec2i a, Vec2i b);
bool eq_vec(Vec2i a, Vec2i b);
int man_dist(Vec2i a, Vec2i b);

Vec2iList* create_vec2i_list(Vec2i pos);
void push_vec2i_list(Vec2iList **headref, Vec2i pos);
Vec2i pop_vec2i_list(Vec2iList **headref);
int count_vec2i_list(Vec2iList *headref);
void destroy_vec2i_list(Vec2iList **headref);

Vec2iList* bh_line(Vec2i start, Vec2i finish);
void bh_line_add(Vec2iList **head, Vec2i pos); 
bool vec2i_list_contains(Vec2iList *head, Vec2i pos);
#endif
