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
    if(check_flag(events, EV_MOVE)) {
        player_move();
        events = remove_flag(events, EV_MOVE);
    }
    if(check_flag(events, EV_OPEN)) {
        open_door(add_vec(get_direction("Open"), g_player->pos));
        events = remove_flag(events, EV_OPEN);
    }
    if(check_flag(events, EV_CLOSE)) {
        close_door(add_vec(get_direction("Close"), g_player->pos));
        events = remove_flag(events, EV_CLOSE);
    }
    if(check_flag(events, EV_DN)) {
        if(get_glyphch_at(g_player->pos.x,g_player->pos.y) == '>') {
            change_level(1);
            events = remove_flag(events, EV_DN);
        } 
    }
    if(check_flag(events, EV_UP)) {
        if(get_glyphch_at(g_player->pos.x, g_player->pos.y) == '<') {
            change_level(-1);
            events = remove_flag(events, EV_UP);
        }
    }
    return events;
}

void player_move(void) {
    Vec2i dpos = g_player->dpos;
    /* Will check for entities at location here */
    /* Check tile at location */
    int dposMask = get_tflags_at(dpos.x,dpos.y);

    if(check_flag(dposMask, TF_BLK_MV)){
        /* Tile blocks movment, is it a door? */
        if(check_flag(dposMask, TF_CDOOR)) {
            /* Is door locked check will go here */
            open_door(dpos);
        }
    } else {
        /* Tile does not block movement */
        g_player->pos.y = g_player->dpos.y;
        g_player->pos.x = g_player->dpos.x;
        g_player->glyph.bg = get_glyphbg_at(dpos.x,dpos.y);
        update_fov();
    }
}

void open_door(Vec2i pos) {
    int mask = get_tflags_at(pos.x,pos.y);
    /*check to see if there is even a closed door at the location first */
    if(check_flag(mask, TF_CDOOR)) {
        place_tile(pos, TILE_ODOOR);
        update_fov();
    }
}

void close_door(Vec2i pos) {
    int mask = get_tflags_at(pos.x,pos.y);
    /*check to see if there is even an open door at the location first */
    if(check_flag(mask, TF_ODOOR)) {
        place_tile(pos, TILE_CDOOR);
        update_fov();
    }
}

void change_level(int shift) {
   /* Eventually this will change the current level up/down by shift */
    if(shift == -1) {
        /* Going up */
        if(g_mapcur != NULL) {
            g_mapcur = g_mapcur->prev;
            g_tilemap = g_mapcur->tiles;
            set_player_pos(find_down_stairs());
        }
    } else if (shift == 1) {
        /* Going down */
        if(g_mapcur->next != NULL) {
            g_mapcur = g_mapcur->next;
            g_tilemap = g_mapcur->tiles;
            set_player_pos(find_up_stairs());
        } else {
            /* We're at the bottom, add a new map on the map list */
            append_map(&g_maphead, NULL);
            g_mapcur = g_mapcur->next;
            g_tilemap = g_mapcur->tiles;
            build_dungeon();
        }
    } else {
        /* Going somewhere? */
    }
    update_fov();
}
