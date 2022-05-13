#include <goblincaves.h>

const int SCREEN_WIDTH = 100;
const int SCREEN_HEIGHT = 40; /* Arbitrary dimensions, for now */
Glyph* g_screen;

Glyph* create_screen(void) {
    Glyph* newScreen = calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(Glyph));

    for(int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        newScreen->ch = '.';
        newScreen->color = 0;
    }

    return newScreen;
}

int get_index(int x, int y) {
    return (x + (SCREEN_WIDTH * y));
}

void draw_screen(void) {
/* Willl attempt to divorce the main loop from the curses engine - draw translates the
 * game screen (glyphs - x,y,fg,bg) into a window screen to be drawn by 
 * whichever render is being used (only curses for now, but ability to change in
 * the future is important to me. */
    int x, y, index;
    clear();
    for (x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_index(x, y);
            mvaddch(y, x, g_screen->ch);
        }
    }
    if(g_player) {
        mvaddch(g_player->pos.y, g_player->pos.x, g_player->glyph.ch);
    }
}

void destroy_screen(void) {
    if(NULL != g_screen) {
        free(g_screen);
    }
}
