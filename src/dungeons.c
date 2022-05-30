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
    int x,y,w,h,i;
    Rect newRoom;
    bool intersects;
    int numRooms = 0;
    int attempts = 0;
    Rect rooms[MAX_NUM_ROOMS];

    for(i = 0; i < MAX_NUM_ROOMS; i++) {
        rooms[i] = make_rect(-5,-5,0,0);
    }
    while(numRooms < MIN_NUM_ROOMS) {
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
            for(i = 0; i < MAX_NUM_ROOMS; i++) {
               if(rect_intersect(newRoom, rooms[i])) {
                    intersects = true;
                    break;
               } 
            }
            if((newRoom.pos.x + newRoom.dim.x >= MAP_WIDTH) ||
                   (newRoom.pos.y + newRoom.dim.y >= MAP_HEIGHT)) {
                intersects = true;
            }
            if(!intersects) {
                place_room(newRoom);
                rooms[numRooms] = newRoom;
                numRooms += 1;
            }
            attempts++;
        }
    }

    for(i = 0; i < MAX_NUM_ROOMS; i++) {
        if(rooms[i].pos.x < 0) {
            break;
        }
        make_fancy_room(rooms[i]);
    }

    for(i = 0; i < MAX_NUM_ROOMS; i++) {
        if(rooms[i].pos.x < 0) {
            break;
        }
        if(i > 0) {
            place_corridor(get_center(rooms[i]), get_center(rooms[i-1]));
        }
    }
    for(i = 0; i < MAX_NUM_ROOMS; i++) {
        if(rooms[i].pos.x < 0) {
            i--; /* i is now the number of the last room */
            break;
        }
        place_doors(rooms[i]);
    }

    place_tile(get_center(rooms[mt_rand(0,i-1)]), TILE_DN);
    if(g_mapcur->lvl != 0) {
        place_tile(get_center(rooms[i]), TILE_UP);
    } else {
        place_tile(get_center(rooms[i]), TILE_FLOOR);
    }
    g_player->pos = get_center(rooms[i]); 
}
