#include <goblincaves.h>

/* Standard term dimensions, 80x24, minus guiHeight eventually*/
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24; 

Glyph* create_screen(void) {
    Glyph* newScreen = calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(Glyph));

    for(int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        newScreen[i].ch = ' ';
        newScreen[i].fg = WHITE;
        newScreen[i].bg = BLACK;
    }

    return newScreen;
}

int get_screen_index(int x, int y) {
    return (x + (SCREEN_WIDTH * y));
}

Vec2i get_camera(void) {
    Vec2i camera;

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

    return camera;
}
void draw_screen(void) {
    int x, y, index, screenIndex, mapIndex;
    Vec2i screenpos, mappos;
    Vec2i camera = get_camera();

    Glyph *screen = create_screen();
    
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
            if(index > (SCREEN_WIDTH * SCREEN_HEIGHT - 1) ||
               mapIndex > (MAP_WIDTH * MAP_HEIGHT - 1)) {
                /* Unsure why this is necessary, but draw_screen will cause
                 * segfaults without it */
                break;
            }
            if(is_visible(x,y)) {
                mark_explored(x,y);
                screen[index] = get_glyph_at(x,y);
            } else if(is_explored(x,y)) {
                screen[index] = get_glyph_at(x,y);
                if(check_flag(get_tflags_at(x,y), TF_BLK_MV) ||
                        check_flag(get_tflags_at(x,y), TF_UP) ||
                        check_flag(get_tflags_at(x,y), TF_DN)) {
                    screen[index].fg = BLUE;
                } else {
                    screen[index].fg = BLACK;
                }
                screen[index].bg = BLACK;
            }
        }
    }
    /* draw the pickups on the screen */
    
    /* draw the enemies on the screen */

    /* draw the player on the screen */
    if(g_player) {
        x = g_player->pos.x - camera.x;
        y = g_player->pos.y - camera.y;
        index = get_screen_index(x,y);
        screen[index].ch = g_player->glyph.ch;
        screen[index].fg = g_player->glyph.fg;
        screen[index].bg = g_player->glyph.bg;
    }

    for(x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            if(index > (SCREEN_WIDTH * SCREEN_HEIGHT - 1)) {
                break;
            }
            curses_draw(x,y, screen[index]);
        }
    }
    free(screen);
}

void clear_screen(Glyph *screen) {
    int x, y, index;
    for (x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            screen[index].ch = ' ';
            screen[index].fg = WHITE;
            screen[index].bg = BLACK;
        }
    }
}

void destroy_screen(Glyph *screen) {
    if(NULL != screen) {
        free(screen);
    }
}
