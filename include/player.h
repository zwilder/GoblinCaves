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
#ifndef PLAYER_H
#define PLAYER_H

typedef struct { 
    Vec2i pos;
    Vec2i dpos;
    Glyph glyph;
    int fovRadius;
} Player;

/********************
 * player.c functions
 ********************/
Player* create_player(Vec2i pos);
void destroy_player(void);

void move_player(Vec2i pos);

#endif 
