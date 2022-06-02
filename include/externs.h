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
#ifndef EXTERNS_H
#define EXTERNS_H

extern Player *g_player; /* Player reference */
extern Map *g_maphead; /* Reference to map list head (level 0) */
extern Map *g_mapcur; /* Reference to current map */
extern Tile *g_tilemap; /* Reference to current tilemap */
extern StateFlags g_gamestate;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int GUI_HEIGHT;
extern const int MSG_HEIGHT;
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern const int MIN_ROOM_SIZE;
extern const int MAX_ROOM_SIZE;
extern const int MIN_NUM_ROOMS;
extern const int MAX_NUM_ROOMS;

#endif
