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

Monster* g_player;
/*
typedef struct { 
    Vec2i pos;
    Vec2i dpos;
    Glyph glyph;
    char name[32];
    int str;
    int dex;
    int per;
    int vit;
    int curhp;
} Monster;
*/
Monster monsterTable[NUM_MON] =
{
    /* pos  dpos  glyph                      name            str dex per vit, flags,            locID,curHP */
    { {0,0},{0,0},{'%',RED,BLACK},         "Corpse"          ,0,0,0,0, MF_NONE,                     0,0},
    { {0,0},{0,0},{'g',GREEN,BLACK},       "Goblin"          ,2,3,2,2, MF_ALIVE,                    0,0},
    { {0,0},{0,0},{'g',BRIGHT_GREEN,BLACK},"Goblin Archer"   ,2,3,3,1, MF_ALIVE | MF_ARCHER,        0,0},
    { {0,0},{0,0},{'B',BROWN,BLACK},       "Bat"             ,1,3,1,2, MF_ALIVE | MF_SKIRMISH,      0,0}
};

Monster* create_monster_at(Vec2i pos, int type) {
    Monster *newMonster = calloc(1,sizeof(Monster));
    *newMonster = monsterTable[type];
    newMonster->name = malloc((strlen(monsterTable[type].name) + 1) * sizeof(char));
    strcpy(newMonster->name, monsterTable[type].name);
    newMonster->pos.x = pos.x;
    newMonster->pos.y = pos.y;
    newMonster->curhp = get_max_hp(newMonster);
    newMonster->locID = g_mapcur->lvl;
    return newMonster;
}

Monster* create_monster(void) {
    Monster *newMonster = malloc(sizeof(Monster));
    /*
    *newMonster = monsterTable[M_CORPSE];
    */
    newMonster->pos = make_vec(0,0);
    newMonster->dpos = make_vec(0,0);
    newMonster->glyph = make_glyph('%', RED, BLACK);
    //strcpy(newMonster->name, "Corpse");
    newMonster->name = NULL;
    newMonster->str = 0;
    newMonster->dex = 0;
    newMonster->per = 0;
    newMonster->vit = 0;
    newMonster->flags = MF_NONE;
    newMonster->locID = -1;
    newMonster->curhp = 0;
    return newMonster;
}

void destroy_monster(Monster* monster) {
    if(monster) {
        free(monster->name);
        monster->name = NULL;
        free(monster);
        monster = NULL;
    }
}

Monster* create_player(MList **head) {
    /* Player creation will eventually have it's own state */
    Monster* newPlayer = calloc(1, sizeof(Monster));

    newPlayer->pos = make_vec(0,0);
    newPlayer->dpos = newPlayer->pos;
    newPlayer->glyph = make_glyph('@', BRIGHT_WHITE, BLACK);

    newPlayer->str = mt_rand(5,10);
    newPlayer->dex = mt_rand(5,10);
    newPlayer->vit = mt_rand(5,10);
    newPlayer->per = mt_rand(5,10);

    newPlayer->curhp = get_max_hp(newPlayer);
    newPlayer->flags = MF_ALIVE | MF_PLAYER;
    newPlayer->locID = 0;

    push_mlist(head, newPlayer);
    
    return newPlayer;
}

void destroy_player(void) {
    if(NULL != g_player) {
        free(g_player);
    }
}

void set_player_pos(Vec2i pos) {
    g_player->pos = pos;
    g_player->glyph.bg = get_glyphbg_at(pos.x,pos.y);
    update_fov();
}

/* If I do change these to be more generic, they should go in their own file,
 * "stats.c" or something. ORGANIZED. */
int get_fov(Monster *monster) {
    /* Just returning the perception, for now.
     * Might be useful to have this accept the perception/vitality as input then
     * calculate the FOV to return... for monsters and stuff? */
    return monster->per;
}

int get_max_hp(Monster *monster) {
    /* Again, just winging this for now. AND AGAIN, might be better to accept
     * the vit/str inputs, then calculate and return the hp */
    return (monster->vit + monster->str) * 5;
}

void melee_combat(Monster *atk, Monster *def) {
/* Random assortment of stats, not sure how they will be used so this is
 * just for fun. 
 * Maybe: Damage done is weapon + str
 *        Chance to hit is dex + str
 *        HP is vit + str
 *        FOV Radius is per + vit
 *        Chance to be hit is dex + per
 *        Str 3 Dex 2 Per 2 Vit 2 */
    char msg[80];
    char msgend[80];
    strcpy(msg, atk->name);
    int chancetohit = mt_rand(0,atk->dex + atk->str);
    int defense = mt_rand(0, def->dex + def->per);
    int wpndmg = 10; //temporary
    if(chancetohit > defense) {
        strcat(msg, " tears into ");
        strcpy(msgend, "!");
        strcat(msg, def->name);
        strcat(msg, msgend);
        def->curhp -= mt_rand(atk->str, atk->str + wpndmg);
        push_msg(&g_msghead, msg);
        if(def->curhp <= 0) {
            kill_monster(def);
        }
    } else {
        strcat(msg, " swings at ");
        strcpy(msgend, " and misses!"); 
        strcat(msg, def->name);
        strcat(msg, msgend);
        push_msg(&g_msghead, msg);
    }
}

void kill_monster(Monster *target) {
    char msg[80];
    strcpy(msg, target->name);
    strcat(msg, " collapses in a bloody heap!");
    push_msg(&g_msghead, msg);
    destroy_mlist_monster(&g_mlist, target);
}
