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
    EV_UP              = 1 << 6,
    EV_SAVE            = 1 << 7,
    EV_LOAD            = 1 << 8,
    EV_CHST_MENU       = 1 << 9,
    EV_CHST_LOAD       = 1 << 10,
    EV_CHST_GAME       = 1 << 11,
    EV_CHST_HELP       = 1 << 12,
    EV_CHST_NWPL       = 1 << 13,
    EV_CHST_LOG        = 1 << 14,
    EV_PLAYER_KP       = 1 << 15,
    EV_CHST_INV        = 1 << 16
} EventFlags;

typedef enum {
    MF_NONE            = 1 << 0,
    MF_PLAYER          = 1 << 1,
    MF_ALIVE           = 1 << 2,
    MF_RANGED          = 1 << 3,
    MF_SKIRMISH        = 1 << 4,
    MF_AFRAID          = 1 << 5,
    MF_SLEEP           = 1 << 6,
    MF_HAS_TURN        = 1 << 7,
    MF_NECRO           = 1 << 8,
    MF_SEENPLAYER      = 1 << 9,
    MF_PACK            = 1 << 10,
    MF_EXPLORING       = 1 << 11,
    MF_MOVE            = 1 << 12,
    MF_OPENDOOR        = 1 << 13,
    MF_CLOSEDOOR       = 1 << 14,
    MF_MVDNSTAIRS      = 1 << 15,
    MF_MVUPSTAIRS      = 1 << 16
} MonsterFlags;

typedef enum {
    ST_MENU =  0,
    ST_GAME,
    ST_HELP,
    ST_NWPL,
    ST_LOG,
    ST_GAMEOVER,
    ST_INV
} StateFlags;

bool check_flag(int mask, int flag);
int toggle_flag(int mask, int flag);
int remove_flag(int mask, int flag);
int engage_flag(int mask, int flag);

#endif
