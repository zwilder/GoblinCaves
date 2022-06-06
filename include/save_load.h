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
#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

/**************************
 * Saving/Loading functions
 * save_load.c
 **************************/
void save_tile(Tile tile, FILE *f);
Tile load_tile(FILE *f);

void save_map(Map **headref, FILE *f);
Map* load_map(FILE *f);

void save_monster(Monster *player, FILE *f);
Monster* load_monster(FILE *f);

int save_game(void);
int load_game(void);

#endif
