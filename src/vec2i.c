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
