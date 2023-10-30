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

/* Newest attempt */
int update(int events) {
    
    switch(check_event(events)) {
        case EV_CHST_NWPL: g_gamestate = ST_NWPL; break;
        case EV_CHST_GAME: g_gamestate = ST_GAME; break;
        case EV_CHST_MENU: g_gamestate = ST_MENU; break;
        case EV_CHST_HELP: g_gamestate = ST_HELP; break;
        case EV_CHST_LOG: g_gamestate = ST_LOG; break;
        case EV_CHST_INV: g_gamestate = ST_INV; break;
        case EV_CHST_GAMEOVER: g_gamestate = ST_GAMEOVER; break;
    }
    events = remove_flag(events, check_event(events));
    if(g_gamestate == ST_GAME) {
        events |= update_game(events);
    }
    return events;
}

int update_game(int events) {
    MList *mlistit = g_mlist;
    bool playerbreak = false;
    while(!playerbreak) {
        /* Need to keep looping through the mlist until the player can take
         * their turn */
        /* Any animations would go HERE. Ideally, there will be a global list of
         * an animations, and if it's not empty, we'd pop them off the top of
         * the list here and play them until the list is empty */
        /* TODO: This needs to be fixed so that everyone who can update updates
         * before they take their turn. Possibly need to add them to another
         * list or something? */
        /* Engine draw fixes not drawing things where they are when the player
         * sees them, but breaks the message drawing and GUI display... 
         * 
         * The problem here is that things are drawing directly to the screen
         * (of course it can't be a simple fix haha) - Everything SHOULD be
         * drawing to a buffer (eg Tile *g_screenbuf) and the draw routines
         * should be ONLY drawing whats on the buffer. Currently, the drawing
         * routines also clear messages off the message list and put them on the
         * message head AND draw the messages directly on the screen. I should
         * be able to call engine_draw directly here to "refresh" what the
         * player sees (by drawing the damn buffer). This needs to be fixed
         * before animations are added.
         *
         * */
        //engine_draw();
        if(!check_flag(g_player->flags, MF_ALIVE)) {
            playerbreak = true;
            continue;
        }
        if(mlistit->data == g_player) {
            if(can_take_turn(g_player)) {
                update_player();
                playerbreak = true;
            } else {
                grant_energy(g_player);
            }
        } else {
            if(can_take_turn(mlistit->data)) {
                take_turn(mlistit->data);
                update_monster(mlistit->data);
            } else {
                grant_energy(mlistit->data);
            }
        }
        mlistit = mlistit->next;
        if(!mlistit) mlistit = g_mlist;
    }
    return events;
}


int check_event(int events) {
    int result = EV_NONE;
    check_flag(events, EV_CHST_NWPL) ? result = EV_CHST_NWPL : result;
    check_flag(events, EV_CHST_GAME) ? result = EV_CHST_GAME: result;
    check_flag(events, EV_CHST_MENU) ? result = EV_CHST_MENU: result;
    check_flag(events, EV_CHST_HELP) ? result = EV_CHST_HELP: result;
    check_flag(events, EV_CHST_LOG) ? result = EV_CHST_LOG: result;
    check_flag(events, EV_CHST_INV) ? result = EV_CHST_INV: result;
    check_flag(events, EV_CHST_GAMEOVER) ? result = EV_CHST_GAMEOVER: result;
    return result;
}

void grant_energy(Monster *monster) {
    char *msg = malloc(sizeof(char) * 80);
    monster->energy += 25;
    //snprintf(msg, 80, "%s gains energy, %d", monster->name, monster->energy);
    //write_log(msg);
    free(msg);
}

void update_monster(Monster *monster) {
    if(!check_flag(monster->flags, MF_ALIVE)) return;
    char *msg = malloc(sizeof(char) * 80);
    Monster *target = NULL;
    /* Move Flag */
    if(check_flag(monster->flags, MF_MOVE)) {
        target = monster_at_pos(g_mlist, monster->dpos,g_mapcur->lvl);
        if(target == g_player) {
            /*Moving into a target*/
            melee_combat(monster, target);
        } else if(is_cdoor(monster->dpos.x,monster->dpos.y) &&
                check_flag(monster->flags, MF_HUMANOID)) {
            /*Moving into a closed door, open it if monster has thumbs*/
            place_tile(monster->dpos, TILE_ODOOR);
            update_fov();
            snprintf(msg,80,"The %s opens the door!", monster->name);
            push_msg(&g_msghead, msg);
        } else {
            /*Moving into an open space*/
            monster->pos = monster->dpos;
        }
        monster->flags = remove_flag(monster->flags, MF_MOVE);
    }
    /* Open/Close door flags */
    if(check_flag(monster->flags, MF_OPENDOOR)) {
        if(is_cdoor(monster->dpos.x,monster->dpos.y)) {
            place_tile(monster->dpos, TILE_ODOOR);
        }
        monster->flags = remove_flag(monster->flags, MF_OPENDOOR);
    }
    if(check_flag(monster->flags, MF_CLOSEDOOR)) {
        if(is_odoor(monster->dpos.x,monster->dpos.y)) {
            place_tile(monster->dpos, TILE_CDOOR);
        }
        monster->flags = remove_flag(monster->flags, MF_CLOSEDOOR);
    }

    /* End turn */
    monster->energy -= monster->spd;
    //snprintf(msg, 80, "%s updated!", monster->name);
    //write_log(msg);
 
    free(msg);
}

void update_player(void) {
    /* Update player should only do things added by flags in take_turn */
    if(!g_player) return;
    bool success = false;
    int pflags = g_player->flags;
    Vec2i mpos;
    Monster *mons = NULL;
    char *msg = malloc(80 * sizeof(char));
    if(check_flag(pflags, MF_MOVE)) {
        success = player_move();
        pflags = remove_flag(pflags, MF_MOVE);
    }
    if(check_flag(pflags, MF_OPENDOOR)) {
        success = open_door(add_vec(get_direction("Open"), g_player->pos));
        pflags = remove_flag(pflags, MF_OPENDOOR);
    }
    if(check_flag(pflags, MF_CLOSEDOOR)) {
        success = close_door(add_vec(get_direction("Close"), g_player->pos));
        pflags = remove_flag(pflags, MF_CLOSEDOOR);
    }
    if(check_flag(pflags, MF_MVDNSTAIRS)) {
        if(get_glyphch_at(g_player->pos.x,g_player->pos.y) == '>') {
            change_level(1);
        } else {
            if(mt_bool()){ 
                push_msg(&g_msghead, "You stare at the ground.");
            } else {
                push_msg(&g_msghead, "You stumble.");
            }
            success = true;
        }
        pflags = remove_flag(pflags, MF_MVDNSTAIRS);
    }
    if(check_flag(pflags, MF_MVUPSTAIRS)) {
        if(get_glyphch_at(g_player->pos.x, g_player->pos.y) == '<') {
            change_level(-1);
        } else {
            if(mt_chance(10)) {
                /* Spawn bat at location lol */
                mpos = make_vec(mt_rand(-1,1),mt_rand(-1,1));
                mpos = subtract_vec(g_player->dpos, mpos);
                mons = create_monster_at(mpos,M_BAT);
                push_msg(&g_msghead, "You look up into the darkness... Hey a bat!");
                push_mlist(&g_mlist, mons);
                mons->flags |= MF_SEENPLAYER;
            } else if(mt_bool()) {
                push_msg(&g_msghead, "You look up into the darkness.");
            } else {
                push_msg(&g_msghead, "You stumble.");
            }
            success = true;
        }
        pflags = remove_flag(pflags, MF_MVUPSTAIRS);
    }
    g_player->flags = pflags;
    if(success){
        g_player->energy -= g_player->spd;
        //snprintf(msg, 80, "%s took their turn!", g_player->name);
        //g_player->flags = remove_flag(g_player->flags, MF_HAS_TURN);
        //snprintf(msg,80,"%s took a turn, now has %d energy.", g_player->name,
        //        g_player->energy);
        //snprintf(msg,80,"%s took turn! Energy %d", g_player->name, g_player->energy);
        //write_log(msg);
    }
    //snprintf(msg,80,"%s updated! Energy %d", g_player->name, g_player->energy);
    //write_log(msg);
    free(msg);
}

bool player_move(void) {
    Vec2i dpos = g_player->dpos;
    int dposMask = 0;
    bool success = false;
    /* Will check for entities at location here */
    Monster *target = living_monster_at_pos(g_mlist, dpos, g_mapcur->lvl);
    if(target && (target != g_player)) {
        /* Attack target - temporary */
        //destroy_mlist_monster(&g_mlist, target);
        if(check_flag(target->flags, MF_ALIVE) ) {
            melee_combat(g_player, target);
            success = true;
            return success;
        } else {
            push_msg(&g_msghead, "You step over some mangled remains.");
            success = true;
        }
    }

    target = corpse_at_pos(g_mlist, dpos, g_mapcur->lvl);
    if(target) {
        push_msg(&g_msghead, "You step over some mangled remains.");
    }

    /* Check tile at location */
    dposMask = get_tflags_at(dpos.x,dpos.y);

    if(check_flag(dposMask, TF_BLOOD) && mt_chance(5)) {
        push_msg(&g_msghead, "Your boots leave tracks on the bloody ground.");
    }

    if(check_flag(dposMask, TF_BLK_MV)){
        /* Tile blocks movment, is it a door? */
        if(check_flag(dposMask, TF_CDOOR)) {
            /* Is door locked check will go here */
            success = open_door(dpos);
        }
    } else {
        /* Tile does not block movement */
        set_player_pos(g_player->dpos);
        tile_flavor_msg(g_player->dpos);
        //g_player->energy -= g_player->spd;
        //g_player->flags = remove_flag(g_player->flags, MF_HAS_TURN);
        success = true;
    }
    return success;
}

bool open_door(Vec2i pos) {
    int mask = get_tflags_at(pos.x,pos.y);
    bool success = false;
    /*check to see if there is even a closed door at the location first */
    if(check_flag(mask, TF_CDOOR)) {
        if(mt_bool()) {
            push_msg(&g_msghead, "You open the door.");
        } else if (mt_bool()) {
            push_msg(&g_msghead, "The door creaks open...");
        } else {
            push_msg(&g_msghead, "With some effort, you manage to open the door.");
        }
        place_tile(pos, TILE_ODOOR);
        update_fov();
        success = true;
    } else {
        push_msg(&g_msghead, "What door?");
    }
    return success;
}

bool close_door(Vec2i pos) {
    int mask = get_tflags_at(pos.x,pos.y);
    bool success = false;
    /*check to see if there is even an open door at the location first */
    if(check_flag(mask, TF_ODOOR)) {
        if(mt_bool()) {
            push_msg(&g_msghead, "You shut the door.");
        } else if (mt_bool()) {
            push_msg(&g_msghead, "The door creaks closed.");
        } else {
            push_msg(&g_msghead, "With some effort, the door closes.");
        }
        place_tile(pos, TILE_CDOOR);
        update_fov();
        success = true;
    } else {
        push_msg(&g_msghead, "What door?");
    }
    return success;
}

void change_level(int shift) {
   /* Eventually this will change the current level up/down by shift */
    if(shift == -1) {
        /* Going up */
        if(g_mapcur != NULL) {
            g_mapcur = g_mapcur->prev;
            g_player->locID = g_mapcur->lvl;

            g_tilemap = g_mapcur->tiles;
            set_player_pos(find_down_stairs());
            push_msg(&g_msghead, "You climb up towards the surface.");
        }
    } else if (shift == 1) {
        /* Going down */
        if(g_mapcur->next != NULL) {
            g_mapcur = g_mapcur->next;
            g_player->locID = g_mapcur->lvl;

            g_tilemap = g_mapcur->tiles;
            set_player_pos(find_up_stairs());
        } else {
            /* We're at the bottom, add a new map on the map list */
            append_map(&g_maphead, NULL);

            g_mapcur = g_mapcur->next;
            g_player->locID = g_mapcur->lvl;

            g_tilemap = g_mapcur->tiles;
            build_dungeon();
        }
        push_msg(&g_msghead, "You descend further into the caves.");
    } else {
        /* Going somewhere? */
    }
    update_fov();
}
