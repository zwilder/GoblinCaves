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
#ifndef UPDATE_H
#define UPDATE_H

/********************
 * update.c functions
 ********************/
int update(int events);
int update_newpl(int events);
int update_game(int events);
int check_event(int events);
void update_monster(Monster *monster);
void grant_energy(Monster *monster);
void update_player(void);
bool player_move(void);
bool open_door(Vec2i pos);
bool close_door(Vec2i pos);
void change_level(int shift);

#endif
