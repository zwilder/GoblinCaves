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
#include <goblincaves.h>

Player* create_player(Vec2i pos) {
    Player* newPlayer = malloc(sizeof(Player));

    newPlayer->pos.y = pos.y;
    newPlayer->pos.x = pos.x;

    newPlayer->dpos.y = pos.y;
    newPlayer->dpos.x = pos.x;

    newPlayer->glyph.ch = '@';
    newPlayer->glyph.fg = BRIGHT_WHITE; 
    newPlayer->glyph.bg = BLACK;
    newPlayer->fovRadius = 6;
    
    return newPlayer;
}

void destroy_player(void) {
    if(NULL != g_player) {
        free(g_player);
    }
}

