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
#ifndef FLAGS_H
#define FLAGS_H

/*******
 * Flags
 *******/

typedef enum {
    TF_NONE            = 1 << 0,
    TF_VIS             = 1 << 1,
    TF_BLK_MV          = 1 << 2,
    TF_EXP             = 1 << 3,
    TF_BLK_LT          = 1 << 4,
    TF_ODOOR           = 1 << 5,
    TF_CDOOR           = 1 << 6,
    TF_UP              = 1 << 7,
    TF_DN              = 1 << 8,
    TF_WATER           = 1 << 9,
    TF_ALTAR           = 1 << 10
} TileFlags;

typedef enum {
    EV_NONE            = 1 << 0,
    EV_QUIT            = 1 << 1,
    EV_MOVE            = 1 << 2,
    EV_OPEN            = 1 << 3,
    EV_CLOSE           = 1 << 4,
    EV_DN              = 1 << 5,
    EV_UP              = 1 << 6
} EventFlags;

bool check_flag(int mask, int flag);
int toggle_flag(int mask, int flag);
int remove_flag(int mask, int flag);
int engage_flag(int mask, int flag);

#endif
