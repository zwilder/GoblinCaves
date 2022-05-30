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
    keypad(stdscr, true);

    if(has_colors()) {
        success = true;
        start_color();
        init_colorpairs();
    } else {
        /* System does not support color, print error message */
        mvprintw(LINES / 2, (COLS / 2) - 28, "Your system does not support color, unable to start game!");
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
    int input;
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

void draw_menu(void) {
    /* Temporary function, just to test out the menu before states are added */
    int artWidth = 54;
    int artHeight = 23;
    int xoff = (COLS / 2) - (artWidth / 2);
    int yoff = (LINES / 2) - (artHeight / 2);
    erase();
    setcolor(BROWN,BLACK);
    mvprintw(yoff,xoff,"  __\\   /__\\|_____|   /_____\\  /\\/_________\\   /______");
    mvprintw(yoff + 1, xoff,"     \\ /          |  /       \\/             \\ /");
    unsetcolor(BROWN,BLACK);
    setcolor(BRIGHT_GREEN,BLACK);
    mvprintw(yoff + 2, xoff," _______  _______ |/_____   _       ________\\/");
    mvprintw(yoff + 3, xoff,"(  ____ \\(  ___  )(  ___ \\ ( \\      \\__   __/( (    /|");
    mvprintw(yoff + 4, xoff,"| (    \\/| (   ) || (   ) )| (         ) (   |  \\  ( |");
    mvprintw(yoff + 5, xoff,"| |      | |   | || (__/ / | |         | |   |   \\ | |");
    mvprintw(yoff + 6, xoff,"| | ____ | |   | ||  __ (  | |         | |   | (\\ \\) |");
    mvprintw(yoff + 7, xoff,"| | \\_  )| |   | || (  \\ \\ | |         | |   | | \\   |");
    mvprintw(yoff + 8, xoff,"| (___) || (___) || )___) )| (____/\\___) (___| )  \\  |");
    mvprintw(yoff + 9, xoff,"(_______)(_______)|/ \\___/ (_______/\\_______/|/    )_)");
    mvprintw(yoff + 10, xoff,"    (  ____ \\(  ___  )|\\     /|(  ____ \\(  ____ \\");
    mvprintw(yoff + 11, xoff,"    | (    \\/| (   ) || )   ( || (    \\/| (    \\/");    
    mvprintw(yoff + 12, xoff,"    | |      | (___) || |   | || (__    | (_____");
    mvprintw(yoff + 13, xoff,"    | |      |  ___  |( (   ) )|  __)   (_____  )");
    mvprintw(yoff + 14, xoff,"    | |      | (   ) | \\ \\_/ / | (            ) |");
    mvprintw(yoff + 15, xoff,"    | (____/\\| )   ( |  \\   /  | (____/\\/\\____) |");
    mvprintw(yoff + 16, xoff,"    (_______/|/ /|  \\|   \\_/   (_______/\\_______) /\\");
    unsetcolor(BRIGHT_GREEN,BLACK);
    setcolor(BROWN,BLACK);
    mvprintw(yoff + 17, xoff,"    /\\         / |      /\\               /\\      /  \\");
    mvprintw(yoff + 18, xoff,"___/  \\___/ \\_/  |_____/  \\|\\______/\\___/  \\____/    \\");
    unsetcolor(BROWN,BLACK);
    setcolor(BRIGHT_WHITE,BLACK);
    mvprintw(yoff + 19, xoff,"[a] - New Adventure                   [c] - High Scores");
    mvprintw(yoff + 20, xoff,"[b] - Load Adventure                  [d] - Quit");
    unsetcolor(BRIGHT_WHITE,BLACK);
    setcolor(WHITE,BLACK);
    mvprintw(yoff + 22, xoff,"                -- ©Zach Wilder 2022 --");
    unsetcolor(WHITE,BLACK);

    /* Fix characters that should be brown not bright green */
    setcolor(BROWN,BLACK);
    mvprintw(yoff + 2, xoff + 18, "|/");
    mvprintw(yoff + 2, xoff + 44, "\\/");
    mvprintw(yoff + 16, xoff + 16, "/|");
    mvprintw(yoff + 16, xoff + 50, "/\\");
    unsetcolor(BROWN,BLACK);
    refresh();
    getch();
}

void draw_help(void) {
    /* Not thrilled with this, but it works for now */
    int artWidth = 80;
    int artHeight = 20;
    int xoff = (COLS / 2) - (artWidth / 2);
    int yoff = (LINES / 2) - (artHeight / 2);
    erase();
    setcolor(BLACK,WHITE);
    mvprintw(yoff,xoff,"                                                                               ");
    mvprintw(yoff + 1,xoff,"                                   - Help -                                    ");
    mvprintw(yoff + 2,xoff,"                                                                               ");
    unsetcolor(BLACK,WHITE);
    setcolor(WHITE,BLACK);
    mvprintw(yoff + 4,xoff,"q : Quit                        ? : Show help screen");
    mvprintw(yoff + 5,xoff,"o : Open");
    mvprintw(yoff + 6,xoff,"c : Close");
    mvprintw(yoff + 7,xoff,"< : Move up stairs");
    mvprintw(yoff + 8,xoff,"> : move down stairs");

    mvprintw(yoff + 10,xoff,"y k u");
    mvprintw(yoff + 11,xoff," \\|/");
    mvprintw(yoff + 12,xoff,"h-.-l    : Movement, vi keys");
    mvprintw(yoff + 13,xoff," /|\\");
    mvprintw(yoff + 14,xoff,"b j n");

    mvprintw(yoff + 16,xoff,"   ^");
    mvprintw(yoff + 17,xoff,"<- v ->  : Movement, arrow keys");
    unsetcolor(WHITE,BLACK);
    setcolor(BLACK,WHITE);
    mvprintw(yoff + 19,xoff,"                           - Press any key to exit -                            ");
    unsetcolor(BLACK,WHITE);
    refresh();
    getch();
}

void curses_close(void) {
    /* Stupid function for now, but there may be other cleanup added later */
    endwin();
}
