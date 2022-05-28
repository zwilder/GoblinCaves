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

/*
 * FOV adapted from the psuedocode by Elig on roguebasin:
 * http://roguebasin.com/index.php/Eligloscode
 */

void update_fov(void) {
    float x,y;
    int i,j;

    /* Set all tiles to not visible */
    for(i = 0; i < MAP_WIDTH; i++) {
        for(j = 0; j < MAP_HEIGHT; j++) {
            remove_tflags_at(i,j, TF_VIS);
        }
    }

    for(i = 0; i < 360; i++){
        x = cos((float)(i * 0.01745f));
        y = sin((float)(i * 0.01745f));
        calculate_fov(x,y);
    }
}

void calculate_fov(float x, float y) {
    int i, mapIndex;
    float ox, oy;

    ox = (float) g_player->pos.x + 0.5f;
    oy = (float) g_player->pos.y + 0.5f;

    for(i = 0; i < g_player->fovRadius; i++) {
        mapIndex = get_map_index((int)ox,(int)oy);
        if(mapIndex > (MAP_WIDTH * MAP_HEIGHT - 1)){
            break;
        }
        engage_tflags_at((int)ox,(int)oy, TF_VIS);
        if(check_tflags_at((int)ox,(int)oy, TF_BLK_LT)){
            return;
        }
        ox += x;
        oy += y;
    }
}
