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

bool curses_setup(void) {
    bool success = false;

    initscr();
    noecho();
    curs_set(0);
    cbreak();

    if(has_colors()) {
        success = true;
        start_color();
        init_colorpairs();
    } else {
        /* System does not support color, print error message */
        mvprintw(20, 50, "Your system does not support color, unable to start game!");
        getch();
    }
    return success;
}

void setcolor(int fg, int bg) {
    /* Set the color pair (colornum) and bold/bright (A_BOLD) */
    attron(COLOR_PAIR(colornum(fg,bg)));
    if(is_bold(fg)) {
        attron(A_BOLD);
    }
}

void unsetcolor(int fg, int bg) {
    /* Unset the color pair (colornum) and bold/bright (A_BOLD) */
    attroff(COLOR_PAIR(colornum(fg,bg)));
    if(is_bold(fg)) {
        attroff(A_BOLD);
    }
}

void curses_draw(int x, int y, Glyph glyph) {
    int xoffset = COLS / 2; /* terminal center x */
    int yoffset = LINES / 2; /* terminal center y */

    xoffset -= SCREEN_WIDTH / 2;
    yoffset -= SCREEN_HEIGHT / 2;

    setcolor(glyph.fg, glyph.bg);
    mvaddch(y + yoffset, x + xoffset, glyph.ch);
    unsetcolor(glyph.fg, glyph.bg);
}

void msg_box(char* msg, Color fg, Color bg) {
    /* Simple message box, displayed at the center of the screen. Will probably
     * need tweaking for fancy things like line wrapping, etc */
    int msglength = strlen(msg);
    int i,j,x,y;
    int boxHeight = 1;
    x = (COLS / 2) - (msglength / 2);
    y = (LINES / 2);
    setcolor(fg,bg);
    for(i = -1; i <= msglength; i++) {
        for(j = 0 - boxHeight; j <= boxHeight; j++) {
            mvaddch(y + j, x + i, ' ');
        }
    }
    mvprintw(y, x, msg);
    unsetcolor(fg,bg);
}

bool yn_prompt(char* msg, Color fg, Color bg) {
    int msglength = strlen(msg);
    int i,j,x,y;
    int boxHeight = 1;
    char input;
    x = (COLS / 2) - (msglength / 2);
    y = (LINES / 2);
    while(true) {
        setcolor(fg,bg);
        for(i = -1; i <= msglength; i++) {
            for(j = 0 - boxHeight; j <= boxHeight + 1; j++) {
                mvaddch(y + j, x + i, ' ');
            }
        }
        mvprintw(y, x, msg);
        mvprintw(y + 1, x + msglength - 6, "[y/n]");
        unsetcolor(fg,bg);
        input = getch();
        switch(input) {
            case 'y':
            case 'Y':
                return true;
                break;
            case 'n':
            case 'N':
                return false;
                break;
            default:
                break;
        }
    }
}

void curses_close(void) {
    /* Stupid function for now, but there may be other cleanup added later */
    endwin();
}
