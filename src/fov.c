#include <goblincaves.h>

/*
 * FOV adapted from the psuedocode by Elig on roguebasin:
 * http://roguebasin.com/index.php/Eligloscode
 */

void update_fov(void) {
    float x,y;
    int i;

    /* Set all tiles to not visible */
    for(i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        g_map[i].flags  &= ~TF_VIS;
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
        g_map[mapIndex].flags |= TF_VIS;
        if(check_flag(g_map[mapIndex].flags, TF_BLK_LT)) {
            return;
        }
        ox += x;
        oy += y;
    }
}
