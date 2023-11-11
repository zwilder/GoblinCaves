/*
* Toolbox
* Copyright (C) Zach Wilder 2022-2023
* 
* This file is a part of Toolbox
*
* Toolbox is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Toolbox is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Toolbox.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <toolbox.h>

/*****
 * Glyph
 * 
 * This file contains another set of useful functions that I tend to write
 * copies of for every project. It relies on vec2i.h.
 *
 * A Glyph is a container holding a single char, an integer foreground color,
 * and an integer background color (see color.h).
 *
 * A screen is a 1 dimensional array of Glyph - and the index related to the x,y
 * coordinates can be found with get_screen_index(x,y). 
 *
 * Ideally, however the application is **actually** drawing the screen can just
 * use these functions to make a screen, write to the screen, and then draw the
 * screen however (X11, SDL, NCurses, PFM, etc).
 *
 *****/
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24; 

Glyph make_glyph(char ch, int fg, int bg) {
    /* Returns a Glyph with char ch, int fg foreground, int bg background */
    Glyph glyph = {};
    glyph.ch = ch;
    glyph.fg = fg;
    glyph.bg = bg;
    return glyph;
}

Glyph* create_screen(void) {
    /* This function allocates memory for the array of glyphs that contain the
     * "screen" that is drawn to, then initializes the entire screen with blank
     * spaces (' ', white text/black background).
     */ 
    Glyph *newScreen = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Glyph));
    int i;
    for(i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        newScreen[i].ch = ' ';
        newScreen[i].fg = 0;
        newScreen[i].bg = 0;
    }

    return newScreen;
}

int get_screen_index(int x, int y) {
    /* The screen array is one dimensional, this takes a coordinate pair and
     * returns the index of the point in the screen array. This function
     * **could** be used with any one dimensional, x/y coordinate array */
    if((x < 0) || (x > SCREEN_WIDTH) || (y < 0) || (y > SCREEN_HEIGHT)) {
        return 0;
    }
    return (x + (SCREEN_WIDTH * y));
}

void set_screen_glyph_at(Glyph *screen, Vec2i pos, Glyph glyph) {
    /* Given an array of glyphs, it sets the glyph at position x,y (pos) to the
     * glyph (glyph) passed in. Really a helper function to avoid typing this
     * repeatedly */
    int index = get_screen_index(pos.x,pos.y);
    screen[index] = glyph;
}

void set_xy_screen_glyph(Glyph *screen, int x, int y, Glyph glyph) {
    /* Same as above, except instead of a vector an x/y pos is passed in. */
    set_screen_glyph_at(screen, make_vec(x,y), glyph);
}

void set_screen_str_at(Glyph *screen, Vec2i pos, char *str, int fg, int bg) {
    int length = strlen(str);
    int i = 0;
    for(i = 0; i < length; i++) {
        set_screen_glyph_at(screen, pos, make_glyph(str[i],fg,bg));
        pos.x++;
    }
}

void set_xy_screen_str(Glyph *screen, int x, int y, char *str, int fg, int bg) {
    set_screen_str_at(screen, make_vec(x,y), str, fg, bg);
}

void clear_screen(Glyph *screen) {
    /* Clears an array of glyphs by setting every glyph in the array to a
     * space (' ') with a black background */
    int x, y, index;
    for (x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            screen[index].ch = ' ';
            screen[index].fg = 0;
            screen[index].bg = 0;
        }
    }
}

void destroy_screen(Glyph *screen) {
    /* If an array of glyphs exists, free the memory. */
    if(NULL != screen) {
        free(screen);
    }
}
