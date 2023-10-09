/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022-2023
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

/* Collection of functions to draw ASCII art - this would be a FANTASTIC thing
 * to put in an external file to read in later. Shoot, doing this in code is
 * verbose. A script file could look something like:
name:tombstone
x,y,char,color_foreground,color_background
...
;
 * Which would allow for things to be easily modified without recompiling the
 * entire dang program (not that that takes any time, really).
 *
 * This file will probably contain the functions to read the .config files for
 * the art. 
 */
void draw_art(int art) {
    /* This makes a screen, and draws art of ART_TYPE art on it */
    Glyph *screen = create_screen();
    int x,y,index;

    switch(art) {
        case ART_TOMBSTONE: draw_tombstone(screen); break;
        default: break;
    }

    for(x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            if(index > (SCREEN_WIDTH * SCREEN_HEIGHT - 1)) {
                break;
            }
            if(screen[index].ch != ' ') {
                curses_draw_main(x,y, screen[index]);
            }
        }
    }
    free(screen);
}

void draw_tombstone(Glyph *screen) {
    /*
     * Tombstone graphic, drawn in REXPaint, Zach Wilder (c) 2018
     * Originally used for "Barbarian!"
     */
    set_xy_screen_glyph(screen, 21,1 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 22,1 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 23,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 24,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 25,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 26,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 27,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 28,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 29,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 30,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 31,1 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen,  9,2 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 19,2 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 20,2 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 21,2 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 22,2 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 32,2 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 33,2 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 8 ,3 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 10,3 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,3 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 19,3 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 20,3 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 34,3 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 35,3 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 17,4 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,4 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 36,4 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen,  2,5 , make_glyph(44,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen,  3,5 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,5 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 17,5 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 37,5 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 1 ,6 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 4 ,6 , make_glyph(96,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 5 ,6 , make_glyph(46,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,6 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,6 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 20,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 23,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 24,6 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 25,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 26,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 28,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 35,6 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 36,6 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 38,6 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 1 ,7 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 2 ,7 , make_glyph(82,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 3 ,7 , make_glyph(73,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 4 ,7 , make_glyph(80,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 5 ,7 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,7 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,7 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,7 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,7 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 20,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 23,7 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 24,7 , make_glyph(92,WHITE,BLACK));
    set_xy_screen_glyph(screen, 25,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 26,7 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,7 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 28,7 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,7 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,7 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,7 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 35,7 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 36,7 , make_glyph(92,WHITE,BLACK));
    set_xy_screen_glyph(screen, 38,7 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 1 ,8 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 5 ,8 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,8 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,8 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,8 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,8 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 20,8 , make_glyph(124,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 21,8 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,8 , make_glyph(47,WHITE,BLACK));
    set_xy_screen_glyph(screen, 23,8 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 24,8 , make_glyph(47,WHITE,BLACK));
    set_xy_screen_glyph(screen, 25,8 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 26,8 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,8 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 28,8 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,8 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,8 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,8 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 32,8 , make_glyph(124,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 33,8 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,8 , make_glyph(47,WHITE,BLACK));
    set_xy_screen_glyph(screen, 35,8 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 36,8 , make_glyph(47,WHITE,BLACK));
    set_xy_screen_glyph(screen, 38,8 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 1 ,9 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 5 ,9 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,9 , make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,9 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,9 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,9 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 20,9 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,9 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,9 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 23,9 , make_glyph(47,WHITE,BLACK));
    set_xy_screen_glyph(screen, 24,9 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 25,9 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 26,9 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,9 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 28,9 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,9 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,9 , make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,9 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,9 , make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,9 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,9 , make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 35,9 , make_glyph(47,WHITE,BLACK));
    set_xy_screen_glyph(screen, 36,9 , make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 38,9 , make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 1 ,10, make_glyph(126,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 4 ,10, make_glyph(126,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 5 ,10, make_glyph(126,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,10, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,10, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,10, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,10, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 20,10, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,10, make_glyph(92,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,10, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 23,10, make_glyph(92,WHITE,BLACK));
    set_xy_screen_glyph(screen, 24,10, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 25,10, make_glyph(95,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 26,10, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,10, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 28,10, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,10, make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,10, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,10, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,10, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,10, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,10, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 35,10, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 36,10, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 38,10, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 3 ,11, make_glyph(126,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,11, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,11, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,11, make_glyph(92,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,11, make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 20,11, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,11, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,11, make_glyph(92,WHITE,BLACK));
    set_xy_screen_glyph(screen, 23,11, make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 24,11, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 25,11, make_glyph(92,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 26,11, make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,11, make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 28,11, make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,11, make_glyph(47,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,11, make_glyph(92,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,11, make_glyph(95,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,11, make_glyph(124,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,11, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 34,11, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 35,11, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 36,11, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 38,11, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,12, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,12, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,12, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,12, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 20,12, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 22,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 23,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 24,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 25,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 26,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 27,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 28,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 29,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 30,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 31,12, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,12, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 34,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 35,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 36,12, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 38,12, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,13, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,13, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 19,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 20,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 21,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 22,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 23,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 24,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 25,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 26,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 27,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 28,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 29,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 30,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 31,13, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,13, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 34,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 35,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 36,13, make_glyph(32,MAGENTA,BLACK));
    set_xy_screen_glyph(screen, 38,13, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,14, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,14, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 38,14, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,15, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,15, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 18,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 19,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 20,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 23,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 24,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 25,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 26,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 28,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 35,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 36,15, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 38,15, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,16, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,16, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 38,16, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,17, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,17, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 17,17, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,17, make_glyph(80,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,17, make_glyph(101,WHITE,BLACK));
    set_xy_screen_glyph(screen, 23,17, make_glyph(114,WHITE,BLACK));
    set_xy_screen_glyph(screen, 24,17, make_glyph(105,WHITE,BLACK));
    set_xy_screen_glyph(screen, 25,17, make_glyph(115,WHITE,BLACK));
    set_xy_screen_glyph(screen, 26,17, make_glyph(104,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,17, make_glyph(101,WHITE,BLACK));
    set_xy_screen_glyph(screen, 28,17, make_glyph(100,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,17, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 38,17, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,18, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,18, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 19,18, make_glyph(98,WHITE,BLACK));
    set_xy_screen_glyph(screen, 20,18, make_glyph(101,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,18, make_glyph(108,WHITE,BLACK));
    set_xy_screen_glyph(screen, 22,18, make_glyph(111,WHITE,BLACK));
    set_xy_screen_glyph(screen, 23,18, make_glyph(119,WHITE,BLACK));
    set_xy_screen_glyph(screen, 24,18, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 25,18, make_glyph(116,WHITE,BLACK));
    set_xy_screen_glyph(screen, 26,18, make_glyph(104,WHITE,BLACK));
    set_xy_screen_glyph(screen, 27,18, make_glyph(101,WHITE,BLACK));
    set_xy_screen_glyph(screen, 28,18, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 29,18, make_glyph(115,WHITE,BLACK));
    set_xy_screen_glyph(screen, 30,18, make_glyph(117,WHITE,BLACK));
    set_xy_screen_glyph(screen, 31,18, make_glyph(114,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,18, make_glyph(102,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,18, make_glyph(97,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,18, make_glyph(99,WHITE,BLACK));
    set_xy_screen_glyph(screen, 35,18, make_glyph(101,WHITE,BLACK));
    set_xy_screen_glyph(screen, 38,18, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 15,19, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,19, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 19,19, make_glyph(111,WHITE,BLACK));
    set_xy_screen_glyph(screen, 20,19, make_glyph(110,WHITE,BLACK));
    set_xy_screen_glyph(screen, 21,19, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 32,19, make_glyph(32,WHITE,BLACK));
    set_xy_screen_glyph(screen, 33,19, make_glyph(119,WHITE,BLACK));
    set_xy_screen_glyph(screen, 34,19, make_glyph(105,WHITE,BLACK));
    set_xy_screen_glyph(screen, 35,19, make_glyph(116,WHITE,BLACK));
    set_xy_screen_glyph(screen, 36,19, make_glyph(104,WHITE,BLACK));
    set_xy_screen_glyph(screen, 38,19, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 40,19, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 41,19, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 42,19, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 15,20, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,20, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 38,20, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 39,20, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 40,20, make_glyph(92,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 41,20, make_glyph(124,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 42,20, make_glyph(47,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 43,20, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 15,21, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,21, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 38,21, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 39,21, make_glyph(45,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 40,21, make_glyph(40,RED,BLACK));
    set_xy_screen_glyph(screen, 41,21, make_glyph(58,RED,BLACK));
    set_xy_screen_glyph(screen, 42,21, make_glyph(41,RED,BLACK));
    set_xy_screen_glyph(screen, 43,21, make_glyph(45,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 44,21, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 15,22, make_glyph(58,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 16,22, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 38,22, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 39,22, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 40,22, make_glyph(47,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 41,22, make_glyph(124,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 42,22, make_glyph(92,BRIGHT_RED,BLACK));
    set_xy_screen_glyph(screen, 43,22, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 16,23, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 38,23, make_glyph(124,BRIGHT_BLACK,BLACK));
    set_xy_screen_glyph(screen, 40,23, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 41,23, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 42,23, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 12,24, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 13,24, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 16,24, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 19,24, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 38,24, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 41,24, make_glyph(124,GREEN,BLACK));
    set_xy_screen_glyph(screen, 44,24, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 13,25, make_glyph(124,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 14,25, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 15,25, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 16,25, make_glyph(34,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 17,25, make_glyph(39,BRIGHT_YELLOW,BLACK));
    set_xy_screen_glyph(screen, 18,25, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 19,25, make_glyph(124,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 20,25, make_glyph(247,GREEN,BLACK));
    set_xy_screen_glyph(screen, 21,25, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 32,25, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 34,25, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 35,25, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 36,25, make_glyph(247,GREEN,BLACK));
    set_xy_screen_glyph(screen, 37,25, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 38,25, make_glyph(124,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 39,25, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 40,25, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 41,25, make_glyph(124,GREEN,BLACK));
    set_xy_screen_glyph(screen, 43,25, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 44,25, make_glyph(124,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 13,26, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 14,26, make_glyph(95,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 15,26, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 16,26, make_glyph(124,GREEN,BLACK));
    set_xy_screen_glyph(screen, 17,26, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 18,26, make_glyph(95,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 19,26, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 22,26, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 23,26, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 24,26, make_glyph(247,GREEN,BLACK));
    set_xy_screen_glyph(screen, 25,26, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 26,26, make_glyph(247,GREEN,BLACK));
    set_xy_screen_glyph(screen, 27,26, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 28,26, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 30,26, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 31,26, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 32,26, make_glyph(126,BROWN,BLACK));
    set_xy_screen_glyph(screen, 33,26, make_glyph(247,GREEN,BLACK));
    set_xy_screen_glyph(screen, 38,26, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 39,26, make_glyph(95,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 40,26, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 41,26, make_glyph(124,GREEN,BLACK));
    set_xy_screen_glyph(screen, 42,26, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 43,26, make_glyph(95,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 44,26, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 27,27, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 28,27, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 29,27, make_glyph(124,GREEN,BLACK));
    set_xy_screen_glyph(screen, 30,27, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 31,27, make_glyph(92,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 39,27, make_glyph(47,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 40,27, make_glyph(95,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 41,27, make_glyph(124,GREEN,BLACK));
    set_xy_screen_glyph(screen, 42,27, make_glyph(95,BRIGHT_GREEN,BLACK));
    set_xy_screen_glyph(screen, 43,27, make_glyph(92,BRIGHT_GREEN,BLACK));
}
