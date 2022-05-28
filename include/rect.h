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
