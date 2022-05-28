#include <goblincaves.h>

/******************
 * Dungeon creation
 ******************/
void draw_dungeon(void) {
    int x, y;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            place_tile(make_vec(x,y), TILE_WALL);
        }
    }
    place_border();

    make_basic_dungeon();
}

void make_basic_dungeon(void) {
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
    /*
    place_tile(get_center(rooms[i]), TILE_UP);
    */
    g_player->pos = get_center(rooms[i]); 
}

