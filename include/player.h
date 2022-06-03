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
#ifndef PLAYER_H
#define PLAYER_H

typedef struct { 
    Vec2i pos;
    Vec2i dpos;
    Glyph glyph;
    char name[32];
    /* Random assortment of stats, not sure how they will be used so this is
     * just for fun. 
     * Maybe: Damage done is weapon + str
     *        Chance to hit is dex + str
     *        HP is vit + str
     *        FOV Radius is per + vit
     *        Chance to be hit is dex + per
     *        Str 3 Dex 2 Per 2 Vit 2 */
    int str;
    int dex;
    int per;
    int vit;
    int curhp;
} Player;

/********************
 * player.c functions
 ********************/
Player* create_player(Vec2i pos);
void destroy_player(void);
int get_fov(Player *player);
int get_max_hp(Player *player);

void set_player_pos(Vec2i pos);

#endif 
