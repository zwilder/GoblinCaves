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
#ifndef LOG_H
#define LOG_H

/*****************
 * log.c functions 
 *****************/
void start_log(void);
void write_log(char *msg);
void log_tilemap(Tile *tilemap, int lvl);
void log_time(void);
void log_vec(Vec2i a);
void log_rect(Rect a);
void log_leaves(Node *node);

#endif 
