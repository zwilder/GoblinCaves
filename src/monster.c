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
    /* pos  dpos  glyph                        name            st,dx,pe,vi,sp, flags,            locID,curHP,en */
    { {0,0},{0,0},{'%',RED,BLACK},           "Corpse"          ,0,0,0,0,0,   MF_NONE,                     0,0,0},
    { {0,0},{0,0},{'g',GREEN,BLACK},         "Goblin"          ,2,3,2,2,100, MF_ALIVE,                    0,0,0},
    { {0,0},{0,0},{'g',BRIGHT_GREEN,BLACK},  "Goblin Archer"   ,2,3,3,1,100, MF_ALIVE | MF_RANGED,        0,0,0},
    { {0,0},{0,0},{'B',BROWN,BLACK},         "Bat"             ,1,3,1,2,50, MF_ALIVE | MF_SKIRMISH,       0,0,0},
    { {0,0},{0,0},{'g',BRIGHT_MAGENTA,BLACK},"Goblin Priest"   ,2,3,4,3,100, MF_ALIVE | MF_NECRO,         0,0,0}
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
    newMonster->spd = 0;
    newMonster->flags = MF_NONE;
    newMonster->locID = -1;
    newMonster->curhp = 0;
    newMonster->energy = 0;
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
    newPlayer->spd = 100;

    newPlayer->flags = MF_ALIVE | MF_PLAYER;
    newPlayer->locID = 0;
    newPlayer->curhp = get_max_hp(newPlayer);
    newPlayer->energy = 0;

    push_mlist(head, newPlayer);
    
    return newPlayer;
}

void destroy_player(void) {
    if(g_player) {
        destroy_monster(g_player);
        g_player = NULL;
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
    char *msg = malloc(80 * sizeof(char));
    int chancetohit = mt_rand(0,atk->dex + atk->str);
    int defense = mt_rand(0, def->dex + def->per);
    int wpndmg = 10; //temporary
    def->flags = remove_flag(def->flags, MF_SLEEP);
    if(chancetohit > defense) {
        if(check_flag(atk->flags, MF_PLAYER)) {
            snprintf(msg,80,"You hit the %s.",def->name);
        } else if(check_flag(def->flags, MF_PLAYER)) {
            snprintf(msg,80,"The %s hits you!",atk->name);
        } else {
            snprintf(msg,80,"%s tears into %s!", atk->name, def->name);
        }
        def->curhp -= mt_rand(atk->str, atk->str + wpndmg);
        push_msg(&g_msghead, msg);
        if(def->curhp <= 0) {
            kill_monster(def);
        }
    } else {
        snprintf(msg,80,"%s swings at %s, and misses!", atk->name, def->name);
        push_msg(&g_msghead, msg);
    }
    free(msg);
}

void kill_monster(Monster *target) {
    /*
    char msg[80];
    strcpy(msg, target->name);
    strcat(msg, " collapses in a bloody heap!");
    */
    char *msg = malloc(80 * sizeof(char));
    if(check_flag(target->flags, MF_PLAYER)) {
        snprintf(msg,80,"Everything goes dark... you die.");
        g_gamestate = ST_GAMEOVER;
    } else if (is_alive(target)) {
        snprintf(msg, 80, "The %s collapses in a bloody heap!", target->name);
    }
    push_msg(&g_msghead, msg);
    //push_mlist(&g_mlist, create_monster_at(target->pos, M_CORPSE));
    destroy_mlist_monster(&g_mlist, target);
    if(target == g_player) {
        g_player = NULL;
    }
    free(msg);
}

bool is_alive(Monster *target) {
    return check_flag(target->flags, MF_ALIVE);
}

void change_state(Monster *monster, int mflagcur, int mflagnext) {
    monster->flags = remove_flag(monster->flags, mflagcur);
    monster->flags = engage_flag(monster->flags, mflagnext);
}

void take_turn(Monster *monster) {
    /* Take turn should add FLAGS not actually do things! 
     * Then, the things are done when the update_monster() function is called. 
     * Should work! */
    char *msg = malloc(80 * sizeof(char));
    //if(!check_flag(monster->flags, MF_HAS_TURN)) {
    //    return; //Monster doesn't have turn
    //}

    if(check_flag(monster->flags, MF_SLEEP)) {
        // Monster is asleep, is player within sight? 
        if(is_explored(monster->pos.x, monster->pos.y)) {
            change_state(monster, MF_SLEEP, MF_SEENPLAYER);
            snprintf(msg,80,"The %s wakes up!",monster->name);
            push_msg(&g_msghead, msg);
        }
    } else if(check_flag(monster->flags, MF_SEENPLAYER)) {
        if(monster->locID != g_mapcur->lvl) {
            change_state(monster, MF_SEENPLAYER, MF_EXPLORING);
        }
        monster->dpos = astar_step(monster->pos, g_player->pos, false);
        //monster->dpos = monster->pos;
        //monster->dpos.x -= mt_rand(-1,1);
        //monster->dpos.y -= mt_rand(-1,1);
        if(vec_null(monster->dpos)) {
            snprintf(msg,80,"The %s howls in fury!", monster->name);
            push_msg(&g_msghead, msg);
            monster->dpos = monster->pos;
        }
        monster->flags = engage_flag(monster->flags, MF_MOVE);
    } else if(check_flag(monster->flags, MF_EXPLORING)) {
        if(is_visible(monster->pos.x, monster->pos.y)) {
            change_state(monster, MF_EXPLORING, MF_SEENPLAYER);
        }
    }
    //monster->flags = remove_flag(monster->flags, MF_HAS_TURN);
    //monster->energy -= monster->spd;
    //snprintf(msg,80,"%s took a turn, now has %d energy.", g_player->name,
    //        g_player->energy);
    //snprintf(msg,80,"%s took a turn.",monster->name);
    //write_log(msg);
    free(msg);
}
