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

int update(int events) {
    if(check_flag(events, EV_CHST_NWPL)) {
        g_gamestate = ST_NWPL;
        events = remove_flag(events, EV_CHST_NWPL);
    }
    if(check_flag(events, EV_CHST_GAME)) {
        g_gamestate = ST_GAME;
        events = remove_flag(events, EV_CHST_GAME);
    }
    if(check_flag(events, EV_CHST_MENU)) {
        g_gamestate = ST_MENU;
        events = remove_flag(events, EV_CHST_MENU);
    }
    if(check_flag(events, EV_CHST_HELP)) {
        g_gamestate = ST_HELP;
        events = remove_flag(events, EV_CHST_HELP);
    }
    if(check_flag(events, EV_CHST_LOG)) {
        g_gamestate = ST_LOG;
        events = remove_flag(events, EV_CHST_LOG);
    }
    /*
     * IDEA! What if... each update loop we only update ONE monster, then
     * advance the turn counter to the next monster for the next loop? We could
     * probably optimize draw if we do this by only drawing when it's the
     * player's turn. We might need to make MList circular, so the last node's
     * next points to the first node. Maybe improve MList by implementing it as
     * a BST or skip list.
     *
     * ANOTHER IDEA: Have a PQ list of monster*, with the priority =
     * monster->energy. check monsters when list is empty for monsters with
     * energy > 0, grant energy to all monsters. Pop off highest priority here,
     * take turn, update ends. */ 
    /* Grant energy */
    /* Take turns */
    /* Pos = dpos */
    if(g_gamestate == ST_GAME) {
        //update_energy();
        update_monsters();
        //if(check_flag(g_player->flags, MF_HAS_TURN)) {
            update_player();
        //}
    }
    return events;
}

void update_energy(void) {
    MList *tmp = NULL;
    char *msg = malloc(80 * sizeof(char));
    for(tmp = g_mlist; tmp; tmp = tmp->next) {
        if(!tmp) {
            break;
        }
        if(tmp->data->locID != g_mapcur->lvl) {
            continue;
        }
        if(check_flag(tmp->data->flags, MF_ALIVE)) {
            tmp->data->energy += 10;
            if(tmp->data->energy > 0) {
                tmp->data->flags = engage_flag(tmp->data->flags, MF_HAS_TURN);
            }
            snprintf(msg,80,"Granting energy to: %s - now has %d energy",
                    tmp->data->name, tmp->data->energy);
            write_log(msg);

        } else {
            tmp->data->energy = 0;
            tmp->data->flags = remove_flag(tmp->data->flags,
                    MF_HAS_TURN);
        }
    }
    free(msg);
}

void update_monsters(void) {
    MList *tmp = NULL;
    Monster *target = NULL;
    Monster *monster = NULL;
    char *msg = malloc(80 * sizeof(char));
    for(tmp = g_mlist; tmp; tmp = tmp->next) {
        if(tmp->data == g_player) {
            continue; //Skip player
        } 
        monster = tmp->data;
        /* If monster moved, update it's position here */
        if(check_flag(monster->flags, MF_MOVE)) {
            target = monster_at_pos(g_mlist, monster->dpos,g_mapcur->lvl);
            /*
            snprintf(msg,80, "%s on DLvl %d is moving: %d,%d to %d,%d",
                    monster->name, g_mapcur->lvl, monster->pos.x,
                    monster->pos.y, monster->dpos.x, monster->dpos.y);
            write_log(msg); 
            */
            if(target) {
                /*Moving into a target*/
                melee_combat(monster, target);
            } else if(is_cdoor(monster->dpos.x,monster->dpos.y)) {
                /*Moving into a closed door, open it*/
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
        //monster->flags = remove_flag(monster->flags, MF_HAS_TURN);
        //monster->energy -= monster->spd;
    }
    free(msg);
}

void update_player(void) {
    if(!g_player) {
        return;
    }
    bool success = false;
    int pflags = g_player->flags;
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
                push_msg(&g_msghead, "You look up into the darkness... Hey a bat!");
                /* Spawn bat at location lol */
                push_mlist(&g_mlist,
                        create_monster_at(subtract_vec(g_player->dpos,
                                make_vec(mt_rand(-1,1),mt_rand(-1,1))), M_BAT));
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
        //g_player->energy -= g_player->spd;
        //g_player->flags = remove_flag(g_player->flags, MF_HAS_TURN);
        //snprintf(msg,80,"%s took a turn, now has %d energy.", g_player->name,
        //        g_player->energy);
        //snprintf(msg,80,"%s took a turn.", g_player->name);
        //write_log(msg);
    }
    free(msg);
}

bool player_move(void) {
    Vec2i dpos = g_player->dpos;
    int dposMask = 0;
    bool success = false;
    /* Will check for entities at location here */
    Monster *target = monster_at_pos(g_mlist, dpos, g_mapcur->lvl);
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
    /* Check tile at location */
    dposMask = get_tflags_at(dpos.x,dpos.y);

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
