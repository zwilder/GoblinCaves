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
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

/*************************
 * game_engine.c functions
 *************************/
void engine_init(void);
void engine_run(void);
void engine_close(void);
int get_input(void);

int mt_rand(int min, int max); 
bool mt_bool(void); 
bool mt_chance(int chance);

void kr_itoa(int n, char s[]);
void kr_reverse(char s[]);

#endif
