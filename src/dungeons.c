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

/******************
 * Dungeon creation
 ******************/
void build_dungeon(void) {
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
