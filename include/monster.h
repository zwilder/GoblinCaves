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
#ifndef MONSTER_H
#define MONSTER_H

typedef struct MList MList;
/* Random assortment of stats, not sure how they will be used so this is
 * just for fun. 
 * Maybe: Damage done is weapon + str
 *        Chance to hit is dex + str
 *        HP is vit + str
 *        FOV Radius is per + vit
 *        Chance to be hit is dex + per
 *        Str 3 Dex 2 Per 2 Vit 2 */
typedef struct { 
    Vec2i pos;
    Vec2i dpos;
    Glyph glyph;
    char *name;
    int str;
    int dex;
    int per;
    int vit;
    int flags;
    int locID;
    int curhp;
} Monster;

typedef enum {
    M_CORPSE    = 0,
    M_GOBLIN,
    M_GARCHER,
    M_BAT,
    M_GPRIEST,
    NUM_MON
} MonsterTypes;

/********************
 * monster.c functions
 ********************/
Monster* create_monster_at(Vec2i pos, int type);
Monster* create_monster(void);
void destroy_monster(Monster* monster);
Monster* create_player(MList **head);
void destroy_player(void);
int get_fov(Monster *monster);
int get_max_hp(Monster *monster);

void set_player_pos(Vec2i pos);

void melee_combat(Monster *atk, Monster *def);
void kill_monster(Monster *target);
bool is_alive(Monster *target);

void take_turn(Monster *monster); 
#endif 
