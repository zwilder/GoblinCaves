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
#ifndef PATHFINDING_H
#define PATHFINDING_H

Vec2iList* bh_line(Vec2i start, Vec2i finish);
void bh_line_add(Vec2iList **head, Vec2i pos); 

Vec2iList* open_neighbors_at(Vec2i pos, bool checkMonsters); 
int movement_cost_at(Vec2i pos);
int movement_cost_to(Vec2i a, Vec2i b); 

Vec2iHT* dijkstra_map(Vec2i start, bool monsterblock);
Vec2i astar_step(Vec2i start, Vec2i goal, bool monsterblock);
Vec2iList* construct_path(Vec2iHT *input, Vec2i start, Vec2i goal);
Vec2iList* astar_path(Vec2i start, Vec2i goal, bool monsterblock); 

#endif 
