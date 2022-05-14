#include <goblincaves.h>

const int SCREEN_WIDTH = 100;
const int SCREEN_HEIGHT = 40; /* Arbitrary dimensions, for now */
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
    int x, y, index;

    /* clear the screen */
    clear_screen();

    /* draw the map (tiles) on the screen */

    /* draw the pickups on the screen */
    
    /* draw the enemies on the screen */

    /* draw the player on the screen */
    if(g_player) {
        x = g_player->pos.x;
        y = g_player->pos.y;
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
