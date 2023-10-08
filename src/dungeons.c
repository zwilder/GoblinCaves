/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022-2023
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

/******************
 * Dungeon creation
 * 
 * This file contains the various algorithms to build dungeons, using the
 * functions in map_features.c
 ******************/

void build_dungeon(void) {
    /* This function fills a map with wall tiles, places a solid border of rock
     * around it, then calls a dungeon building algorithm to carve out rooms. */
    int x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            place_tile(make_vec(x,y), TILE_WALL);
        }
    }
    place_border();

    /* This could be an interesting place to check the current level being built
     * and build in special levels */
    build_basic_dungeon();
}

void build_basic_dungeon(void) {
    /* Basic dungeon building algorithm.
     * First, repeat the following a number of times to generate a list of
     * rooms. We don't worry about what happens if there is too few rooms,
     * because there will always be SOME rooms. It's very rare that the number
     * of rooms is less than the minimum anyways.
     * 1) Pick a random x,y coordinate on the map.
     * 2) Make a rectangle of random width,height
     * 3) Check to see if that rectangle intersects with any of the other
     *    rectangles in the list of rooms. If it does, discard it.
     * 4) Check to see if the rectangle is out of bounds (outside the map). If
     *    it is, discard it.
     * 5) If the rectangle is fine, put the rectangle into the list of rooms.
     * 
     * Next do the following to make the dungeon interesting:
     * 1) Go through the list of rooms, making rooms "fancy" - adding neat
     *    features and spice (from map_features.c).
     * 2) Place cooridors (tunnels) connecting the rooms, adding doors when
     *    necessary. 
     * 3) Place monsters in the rooms.
     * 4) Place items in the rooms (not implemented, yet). TODO
     * 
     * Finally
     * 1) Place the player in the first room, with a staircase leading up
     *    if they are on a level other than the first.
     * 2) Place the staircase leading down in a random room that is not the
     *    first room. 
     */
    int x,y,w,h;
    Rect newRoom;
    bool intersects;
    int numRooms = 0;
    int attempts = 0;
    int minattempts = 0;
    RectList *rooms = NULL;
    RectList *tmp = NULL;

    while(numRooms < MIN_NUM_ROOMS && minattempts < 100) {
        while(numRooms < MAX_NUM_ROOMS && attempts < 500) {
            x = mt_rand(1, MAP_WIDTH - MAX_ROOM_SIZE - 1);
            y = mt_rand(1, MAP_HEIGHT - MAX_ROOM_SIZE - 1);
            w = mt_rand(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
            h = mt_rand(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
            while(x % 2 != 0) {
                x = mt_rand(1, MAP_WIDTH - 1);
            }
            while(y % 2 != 0) {
                y = mt_rand(1, MAP_HEIGHT - 1);
            }
            newRoom = make_rect(x,y,w,h);
            intersects = false;
            tmp = rooms;
            while(tmp) {
                if(rect_intersect(newRoom, tmp->data)) {
                    intersects = true;
                    break;
                }
                tmp = tmp->next;
            }
            if((newRoom.pos.x + newRoom.dim.x >= MAP_WIDTH) ||
                   (newRoom.pos.y + newRoom.dim.y >= MAP_HEIGHT)) {
                intersects = true;
            }
            if(!intersects) {
                place_room(newRoom);
                push_RectList(&rooms, newRoom);
                numRooms = count_RectList(rooms);
            }
            attempts++;
        }
        minattempts++;
    }
    tmp = rooms;
    while(tmp) {
        make_fancy_room(tmp->data);
        tmp = tmp->next;
    }

    tmp = rooms;
    while(tmp->next) {
        place_corridor(get_center(tmp->data), get_center(tmp->next->data));
        tmp = tmp->next; 
    }

    tmp = rooms;
    while(tmp) {
        place_doors(tmp->data);
        if(tmp != rooms) {
            place_monsters(tmp->data);
        }
        tmp = tmp->next;
    }

    /* Get random room */
    x = mt_rand(0, count_RectList(rooms) - 1);
    y = 0;
    tmp = rooms;
    while(y != x) {
        y++;
        tmp = tmp->next;
    }
    place_tile(get_center(tmp->data), TILE_DN);
    if(g_mapcur->lvl != 0) {
        place_tile(get_center(rooms->data), TILE_UP);
    } else {
        place_tile(get_center(rooms->data), TILE_FLOOR);
    }
    g_player->pos = get_center(rooms->data); 
    destroy_RectList(&rooms);
}
