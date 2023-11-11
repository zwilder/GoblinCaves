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

void scr_pt_xclr_char(int x, int y, uint8_t fg, uint8_t bg, char c) {
    /* Print a char at x,y in one of the 256 colors */
    scr_set_xclr(fg,bg);
    scr_pt_char(x,y,c);
}

void scr_pt_clr_char(int x, int y, Color fg, Color bg, char c) {
    /* Print a char at x,y in one of the 8+8 colors */
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

void scr_pt_xclr(int x, int y, uint8_t fg, uint8_t bg, char *fstr,...) {
    /* Print a formatted string in one of the 256 colors */
    va_list args;
    va_start(args, fstr);
    scr_set_curs(x,y);
    scr_set_xclr(fg,bg);
    vprintf(fstr, args);
    fflush(stdout);
    va_end(args);
}

void scr_pt_clr(int x, int y, Color fg, Color bg, char *fstr,...) {
    /* Print a formatted string in one of the 8+8 colors */
    va_list args;
    va_start(args, fstr);
    scr_set_curs(x,y);
    scr_set_clr(fg,bg);
    vprintf(fstr,args);
    fflush(stdout);
    va_end(args);
}

void scr_set_xclr(uint8_t fg, uint8_t bg) {
    printf("\x1b[38;5;%dm\x1b[48;5;%dm",fg,bg);
    fflush(stdout);
}

int get_clr(Color a, bool bg) {
    /* Helper function, since the Color enum was originally created for NCurses,
     * this changes the color from NCurses back to one of the 8+8 colors */
    int r;
    switch(a) {
        case BLACK: r = 30; break;
        case BLUE: r = 34; break;
        case GREEN: r = 32; break;
        case CYAN: r = 36; break;
        case RED: r = 31; break;
        case MAGENTA: r = 35; break;
        case BROWN: r = 33; break;
        case WHITE: r = 37; break;
        case BRIGHT_BLACK: r = 90; break;
        case BRIGHT_BLUE: r = 94; break;
        case BRIGHT_GREEN: r = 92; break;
        case BRIGHT_CYAN: r = 96; break;
        case BRIGHT_RED: r = 91; break;
        case BRIGHT_MAGENTA: r = 95; break;
        case BRIGHT_YELLOW: r = 93; break;
        case BRIGHT_WHITE: r = 97; break;
        default: break;
    }
    if(bg) r+=10;
    return r;
}

void scr_set_clr(Color fg, Color bg) {
    //printf("\x1b[%d;%dm",get_clr(fg,false),get_clr(bg,true));
    printf("\x1b[%d;%dm",fg,bg);
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
        newkbflags.c_cc[VMIN] = 1;
        newkbflags.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &newkbflags);
    }
}

void kb_restore(void) {
    tcsetattr(0,TCSADRAIN,&g_oldkbflags);
}

char kb_get_char(void) {
    char c;
    read(STDIN_FILENO,&c,1);
    return c;
}

char* kb_get_str(void) {
    char* input = malloc(1000 * sizeof(char));
    kb_restore();
    //printf("\x1b[?25h\x1b[3 q");
    printf("\x1b[?25h\x1b[2 q");
    scanf("%[^\n]s",input);
    printf("\x1b[?25l\x1b[0 q");
    kb_init();
    return input;
}

char* kb_get_str_at(int x, int y) {
    scr_set_curs(x,y);
    return kb_get_str();
}
