#include <goblincaves.h>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24; /* Standard term dimensions, for now */
Glyph* g_screen;

Glyph* create_screen(void) {
    Glyph* newScreen = calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(Glyph));

    for(int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        newScreen[i].ch = '.';
        newScreen[i].fg = WHITE;
        newScreen[i].bg = BLACK;
    }

    return newScreen;
}

int get_screen_index(int x, int y) {
    return (x + (SCREEN_WIDTH * y));
}

void draw_screen(void) {
    int x, y, index, screenIndex, mapIndex;
    Vec2i camera, screenpos, mappos;

    /* clear the screen */
    clear_screen();
    
    /* Get the camera */
    camera.x = g_player->pos.x - (SCREEN_WIDTH / 2);
    camera.y = g_player->pos.y - (SCREEN_HEIGHT / 2);

    /* Adjust the camera if the player is too close to the edge */
    if(g_player->pos.x < (SCREEN_WIDTH / 2)) {
        camera.x = 0;
    } else if (g_player->pos.x >= MAP_WIDTH - (SCREEN_WIDTH / 2)) {
        camera.x = 1 + MAP_WIDTH - SCREEN_WIDTH;
    } else {
        camera.x = g_player->pos.x - (SCREEN_WIDTH / 2);
    }
    if(g_player->pos.y < (SCREEN_HEIGHT / 2)) {
        camera.y = 0;
    } else if (g_player->pos.y >= MAP_HEIGHT - (SCREEN_HEIGHT / 2)) {
        camera.y = 1 + MAP_HEIGHT - SCREEN_HEIGHT;
    } else {
        camera.y = g_player->pos.y - (SCREEN_HEIGHT / 2);
    }

    /* draw the map (tiles) on the screen */
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            mappos.x = x;
            mappos.y = y;
            screenpos = subtract_vec(mappos, camera);
            if(screenpos.x < 0 || screenpos.y < 0) {
                continue;
            }
            index = get_screen_index(screenpos.x, screenpos.y);
            mapIndex = get_map_index(x, y);
            if((g_map[mapIndex].flags & TF_VIS) == TF_VIS) {
                g_map[mapIndex].flags |= TF_EXP;
                g_screen[index] = g_map[mapIndex].glyph;
            } else if ((g_map[mapIndex].flags & TF_EXP) == TF_EXP) {
                g_screen[index].ch = g_map[mapIndex].glyph.ch;
                g_screen[index].fg = BLUE;
                g_screen[index].bg = BLACK;
            }
        }
    }
    /* This is only temporary, while MAP_WIDTH and MAP_HEIGHT equal
     * SCREEN_WIDTH and SCREEN_HEIGHT */
    /*
    for(x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            mapIndex = get_map_index(x,y);
            if((g_map[mapIndex].flags & TF_VIS) == TF_VIS) {
                g_map[mapIndex].flags |= TF_EXP;
                g_screen[index] = g_map[mapIndex].glyph;
            } else if ((g_map[mapIndex].flags & TF_EXP) == TF_EXP) {
                g_screen[index].ch = g_map[mapIndex].glyph.ch;
                g_screen[index].fg = BLUE;
                g_screen[index].bg = BLACK;
            }
        }
    }
    */
    /* draw the pickups on the screen */
    
    /* draw the enemies on the screen */

    /* draw the player on the screen */
    if(g_player) {
        x = g_player->pos.x - camera.x;
        y = g_player->pos.y - camera.y;
        index = get_screen_index(x,y);
        g_screen[index].ch = g_player->glyph.ch;
        g_screen[index].fg = g_player->glyph.fg;
        g_screen[index].bg = g_player->glyph.bg;
    }

    curses_draw();
}

void clear_screen(void) {
    int x, y, index;
    for (x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            g_screen[index].ch = ' ';
            g_screen[index].fg = WHITE;
            g_screen[index].bg = BLACK;
        }
    }
}

void destroy_screen(void) {
    if(NULL != g_screen) {
        free(g_screen);
    }
}
