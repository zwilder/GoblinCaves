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
#ifndef MAP_FEATURES_H
#define MAP_FEATURES_H

/*******************
 * Feature placement
 *******************/
void place_room(Rect room);
void make_fancy_room(Rect room);
void place_altar(Rect room);
void place_marsh(Rect room);
void place_pillars(Rect Room);
void round_room(Rect room);
void place_htunnel(int x1, int x2, int y);
void place_vtunnel(int y1, int y2, int x);
void place_orthogonal_tunnel(Vec2i a, Vec2i b);
void place_corridor(Vec2i a, Vec2i b); 
void place_hdoor(int x, int y);
void place_vdoor(int x, int y);
void place_doors(Rect room);
void place_border(void);
void place_monsters(Rect room);

#endif
