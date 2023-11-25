/*
* Terminal Engine 
* Copyright (C) Zach Wilder 2022-2023
* 
* This file is a part of Terminal Engine
*
* Terminal Engine is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Terminal Engine is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Terminal Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <term_engine.h>

/******
 * Terminal Engine
 *
 * This is a collection of functions written to "replace" NCurses, and be more
 * in control of the behavior of the terminal. It is independent of Goblin
 * Caves and The Toolbox, and can be used in other projects.
 *
 * There are two main sets of functions here - drawing functions and keyboard
 * functions. Drawing handles the screen initialization/close, the physical
 * placement of characters on the terminal screen, and styling of characters.
 * Keyboard handles the initialization/resetting of the keyboard mode, and
 * reading character input from the user's keyboard.
 *****/

struct termios g_oldkbflags;
int g_screenW = 0;
int g_screenH = 0;

/******************
 * System functions
 ******************/
void term_init(void) {
    scr_init();
    kb_init();
}

void term_close(void) {
    scr_restore();
    kb_restore();
}

/******************
 * Draw functions
 ******************/
void scr_init(void) {
    struct winsize ws;
    ioctl(0,TIOCGWINSZ,&ws);
    g_screenW = ws.ws_col;
    g_screenH = ws.ws_row;
    printf("\x1b[?1049h"); //Alternate buffer
    printf("\x1b[?25l"); //Hides cursor (l = low,0)
    scr_reset();
    scr_clear();
}

void scr_restore(void) {
    scr_reset();
    scr_clear();
    printf("\x1b[?1049l");
    printf("\x1b[?25h"); //Show cursor (h = high,1)
}

void scr_reset(void) {
    printf("\x1b[0m"); //Reset to default
    fflush(stdout);
}

void scr_clear(void) {
    printf("\x1b[H\x1b[J"); //?
    fflush(stdout);
}

void scr_pt_char(int x, int y, char c) {
    printf("\x1b[%d;%dH%c", y+1,x+1,c); //coordinates start at 1,1
    fflush(stdout);
}

void scr_pt_clr_char(int x, int y, uint8_t fg, uint8_t bg, char c) {
    /* Print a char at x,y in one of the 256 colors */
    scr_set_clr(fg,bg);
    scr_pt_char(x,y,c);
}

void scr_pt(int x, int y, char *fstr,...) {
    /* Print a formatted string at x,y */
    va_list args;
    va_start(args,fstr);
    scr_set_curs(x,y);
    vprintf(fstr, args);
    fflush(stdout);
    va_end(args);
}

void scr_pt_clr(int x, int y, uint8_t fg, uint8_t bg, char *fstr,...) {
    /* Print a formatted string in color */
    va_list args;
    va_start(args, fstr);
    scr_set_curs(x,y);
    scr_set_clr(fg,bg);
    vprintf(fstr, args);
    fflush(stdout);
    va_end(args);
}

void scr_set_clr(uint8_t fg, uint8_t bg) {
    printf("\x1b[38;5;%dm\x1b[48;5;%dm",fg,bg);
    fflush(stdout);
}

void scr_set_curs(int x, int y) {
    printf("\x1b[%d;%dH",y+1,x+1);
}

void scr_set_style(int style) {
    if((style & ST_BOLD) == ST_BOLD) {
        printf("\x1b[1m");
    }
    if((style & ST_DIM) == ST_DIM) {
        printf("\x1b[2m");
    }
    if((style & ST_ITALIC) == ST_ITALIC) {
        printf("\x1b[3m");
    }
    if((style & ST_ULINE) == ST_ULINE) {
        printf("\x1b[4m");
    }
    if((style & ST_BLINK) == ST_BLINK) {
        printf("\x1b[5m");
    }
    if((style & ST_STRIKE) == ST_STRIKE) {
        printf("\x1b[9m");
    }
    if((style & ST_NONE) == ST_NONE) {
        printf("\x1b[0m");
    }
}

/*******************
 * Input functions
 *******************/

void kb_init(void) {
    struct termios newkbflags;
    if(tcgetattr(0, &g_oldkbflags)>=0) {
        tcgetattr(0, &newkbflags);
        newkbflags.c_lflag &= ~ICANON;
        newkbflags.c_lflag &= ~ECHO;
        newkbflags.c_cc[VMIN] = 0;
        newkbflags.c_cc[VTIME] = 1;
        tcsetattr(0, TCSANOW, &newkbflags);
    }
}

void kb_restore(void) {
    tcsetattr(0,TCSADRAIN,&g_oldkbflags);
}

char kb_get_char(void) {
    /* The while loop below makes this function "blocking"; with it commented
     * out this changes to "non-blocking". Could possibly add a bool "blocking"
     * or something as a passed in variable? Or maybe make blocking/nonblocking
     * they're own functions?
     *
     * In kb_init(), the flags VMIN and VTIME are important here, VMIN causes
     * read to return immediately with a keypress, and VTIME causes read to
     * return after a 1/10th second delay with no keypress */
    char c = '\0';
    //while('\0' == c) {
        read(STDIN_FILENO,&c,1);
    //}
    //c = getchar();
    //fgets(&c, 2, stdin);
    return c;
}

char* kb_get_str(int maxsz) {
    /*
     * 1	Blinking block
     * 2	Steady block (default)
     * 3	Blinking underscore
     * 4	Steady underscore
     * 5	Blinking bar
     * 6	Steady bar
     */
    char* input = malloc(maxsz * sizeof(char));
    //char c = '\0';
    kb_restore(); // Restore terminal keyboard
    printf("\x1b[?25h\x1b[1 q"); // Show the cursor
    /* Since scanf(...) is problematic, it **might** be better to rewrite this
     * to use fgets */
    /*
    result = scanf("%[^\n]s",input);
    while((c = getchar()) != '\n' && c != EOF) {
        // Discard the extra chracters
    }
    */
    fgets(input, maxsz, stdin);
    if(input[0] == '\n' || input[0] == '\0') {
        free(input);
        input = NULL;
    }
    printf("\x1b[?25l\x1b[0 q"); // Hide the cursor
    kb_init(); // Reinitialize engine keyboard
    return input;
}

char* kb_get_str_at(int x, int y, int maxsz) {
    scr_set_curs(x,y);
    return kb_get_str(maxsz);
}
