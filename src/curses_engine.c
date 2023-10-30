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

/* One of the goals with this project was to not tie the program to a specific
 * library for visuals - To that end, all the functions that call NCURSES
 * routines directly **should** be in this file. There's a couple of random ones
 * in update.c that need to be addressed. 
 *
 * Really, what should be done at some point is instead of the game calling
 * these functions, it should call a generic function (engine_setup() for
 * example) that calls these functions. This would allow me to add an easy
 * flag check to see what visual library we are using - SDL, NCURSES, etc.
 *
 * Additionally, I really don't have to be using NCURSES at all and can do
 * better printing/input handling with calls to the terminal directly... But I
 * figured that out after all this was written (see the "Cards" project,
 * github.com/zwilder/cards).
 * */
#include <goblincaves.h>

bool curses_setup(void) {
    /* General NCURSES setup routine, calls the NCURSES functions to get the
     * terminal ready for drawing/input */
    bool success = false;

    initscr();
    noecho();
    //nodelay(stdscr, false);
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

void curses_draw_main(int x, int y, Glyph glyph) {
    /* Draws a glyph (char ch, color fg, color bg) at the x,y coordinates on the
     * terminal, making sure to center the screen (program screen) regardless of
     * user terminal size */
    int xoffset = COLS / 2; /* terminal center x */
    int yoffset = LINES / 2; /* terminal center y */

    xoffset -= SCREEN_WIDTH / 2;
    yoffset -= SCREEN_HEIGHT / 2;
    
    /*yoffset -= GUI_HEIGHT;*/ 

    setcolor(glyph.fg, glyph.bg);
    mvaddch(y + yoffset, x + xoffset, glyph.ch);
    unsetcolor(glyph.fg, glyph.bg);
}

void curses_close(void) {
    /* Stupid function for now, but there may be other cleanup added later */
    endwin();
}

/*****
 * Everything below should be rewritten as a function in draw.c to draw to the
 * screen buffer
 *****/

void curses_draw_msg(int x, int y, char *msg) {
    /* Draws a message (msg) at the given x,y coordinates */
    int xoffset = COLS / 2;
    int yoffset = LINES / 2;
    xoffset -= SCREEN_WIDTH / 2;
    yoffset -= SCREEN_HEIGHT / 2;
    yoffset -= MSG_HEIGHT;

    /*
    setcolor(WHITE, BLACK);
    */
    mvprintw(y + yoffset, x + xoffset, msg);
    /*
    unsetcolor(WHITE, BLACK);
    */
}

void curses_draw_titlebar(char *title, Color fg, Color bg) {
    /* Draws a "titlebar" (string centered on the top row of the screen) with
     * the given foreground/background colors */
    int xoffset = COLS / 2;
    int x = xoffset - (SCREEN_WIDTH / 2);
    int yoffset = LINES / 2;
    xoffset -= strlen(title) / 2;
    yoffset -= SCREEN_HEIGHT / 2;
    yoffset -= MSG_HEIGHT;
    
    setcolor(fg,bg);
    for(; x < ((SCREEN_WIDTH / 2) + (COLS / 2)); x++) {
        mvaddch(yoffset,x, ' ');
    }
    mvprintw(yoffset,xoffset,title);
    unsetcolor(fg,bg);
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
    /* Pops up a box in the middle of the screen, requesting a yes/no answer to
     * a question (y/n/Y/N keypress from the user), and returning true if the
     * user answers yes, false if not. Neat! */
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

void error_msg_box(char* msg, Color fg, Color bg) {
    /* Clear's the screen to print a message (msg) in a specifed
     * foreground/background color in the center of the screen, and waiting for
     * a keypress from the user to return */
    erase();
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

    x += (msglength/2);
    y += (SCREEN_HEIGHT / 2);
    unsetcolor(fg,bg);
    setcolor(WHITE, BLACK);
    mvprintw(y, x - 14, "- Press any key to continue -");
    unsetcolor(WHITE, BLACK);
    refresh();
    getch();
}

void draw_nwpl(void) {
    /* This function displays the "New player" screen, which currently just asks
     * for the player to enter a name for their adventurer. If they enter
     * nothing it prints an error asking them to try again. */
    int xoff = (COLS / 2);
    int yoff = (LINES / 2);
    char mesg[] = "What is your name, adventurer? ";
    char str[32];
    erase();
    echo();
    curs_set(1);
    mvprintw(yoff, xoff - (strlen(mesg)/2), "%s", mesg);
    mvprintw(yoff + 1, xoff - (strlen(mesg)/2), ">");
    setcolor(BRIGHT_WHITE, BLACK);
    getstr(str);
    unsetcolor(BRIGHT_WHITE, BLACK);
    while(strlen(str) == 0) {
        /* It would be cool if this whole statement was replaced with a call to
         * a random name generator... */
        setcolor(RED, BLACK);
        mvprintw(yoff + 3, xoff - (strlen(mesg)/2), "[Try again]");
        unsetcolor(RED, BLACK);
        mvprintw(yoff + 1, xoff - (strlen(mesg)/2), ">");
        setcolor(BRIGHT_WHITE, BLACK);
        getstr(str);
        unsetcolor(BRIGHT_WHITE, BLACK);
    }
    refresh();
    noecho();
    curs_set(0);
    g_player->name = strdup(str);
    //strcpy(g_player->name, str);
}

