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
    int x, y, index, screenX, screenY, screenIndex, mapIndex;
    Vec2i pos;
    Rect camera, mapRect;

    /* clear the screen */
    clear_screen();

    /* So the game map is bigger than the screen size. This requires some
     * interpretation then - we need a "camera" to draw a rectangle around the
     * player, check all the entities around the player and add them as adjusted
     * x,y coordinate pairs to the screen.
     * Basically:
     * 1 The player is drawn on the center of the screen
     * 2 The camera coordinates are then set to the rectangle with bounds: 
     *     Rect camera;
     *     camera.dim.x = g_player->pos.x + (screen width / 2);
     *     camera.pos.x = g_player->pos.x - (screen width / 2);
     *     camera.dim.y = g_player->pos.y + (screen height / 2);
     *     camera.pos.y = g_player->pos.y - (screen height / 2 );
     * 3 Draw only the tiles/pickups/enemies whose x,y coordinates are in the
     *   coordinate list. 
     *   bool in_camera(Rect a, Pos b) {
     *      bool x = ((b.x >= a.pos.x) && (b.x <= a.dim.x));
     *      bool y = ((b.y >= a.pos.y) && (b.y <= a.dim.y));
     *      return (x && y);
     *   }
     *   
     *   Loop through all camera coordinates, placing them on the screen
     *   starting at 0,0.
     *   int screenX = 0;
     *   int screenY = 0;
     *   for(int x = camera.pos.x; x <= camera.dim.x; x++) {
     *      for(int y = camera.pos.y; y <= camera.dim.y; y++) {
     *          mapIndex = get_map_index(x, y);
     *          screenIndex = get_screen_index(screenX, screenY);
     *          g_screen[screenIndex].ch = g_map[mapIndex].glyph.ch;
     *          g_screen[screenIndex].fg = g_map[mapIndex].glyph.fg;
     *          g_screen[screenIndex].bg = g_map[mapIndex].glyph.bg;
     *          screenY++;
     *      }
     *      screenX++;
     *   }       
     */

    camera.dim.x = g_player->pos.x + (SCREEN_WIDTH / 2);
    camera.pos.x = g_player->pos.x - (SCREEN_WIDTH / 2);
    camera.dim.y = g_player->pos.y + (SCREEN_HEIGHT / 2);
    camera.pos.y = g_player->pos.y - (SCREEN_HEIGHT / 2);

    /*
    screenX = 0;
    screenY = 0;
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            pos.x = x;
            pos.y = y;
            if(point_in_rect(camera,pos)){
                screenY++;
                g_screen[get_screen_index(screenX,screenY)]=g_map[get_map_index(x,y)].glyph;
            }
        }
        screenY = 0;
        screenX++;
    }
    */
    /* Below causes segfault? */
            /*
    mapRect.pos.x = 0;
    mapRect.pos.y = 0;
    mapRect.dim.x = MAP_WIDTH - 1;
    mapRect.dim.y = MAP_HEIGHT - 1;
    for(x = camera.pos.x; x < camera.dim.x; x++) {
        for(y = camera.pos.y; y < camera.dim.y; y++) {
            pos.x = x;
            pos.y = y;
            if(point_in_rect(mapRect, pos)) {
                mapIndex = get_map_index(x,y);
                screenIndex = get_screen_index(screenX, screenY);
                g_screen[screenIndex].ch = g_map[mapIndex].glyph.ch; //segfault here
                g_screen[screenIndex].fg = g_map[mapIndex].glyph.fg;
                g_screen[screenIndex].bg = g_map[mapIndex].glyph.bg;
                screenY++;
            }
        }
        screenY = 0;
        screenX++;
    }
            */

    /* draw the map (tiles) on the screen */
    for(x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            /* This is only temporary, while MAP_WIDTH and MAP_HEIGHT equal
             * SCREEN_WIDTH and SCREEN_HEIGHT */
            index = get_screen_index(x,y);
            g_screen[index] = g_map[get_map_index(x,y)].glyph;
        }
    }
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
