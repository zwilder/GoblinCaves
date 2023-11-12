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

#ifndef TERM_ENGINE_H
#define TERM_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h> 
#include <stdarg.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/*********
 * Globals
 *********/
extern int g_screenW;
extern int g_screenH;
extern struct termios g_oldkbflags;

/*******
 * Flags
 *******/
typedef enum {
    ST_NONE         = 1 << 0,
    ST_ULINE        = 1 << 1,
    ST_ITALIC       = 1 << 2,
    ST_BLINK        = 1 << 3,
    ST_BOLD         = 1 << 4,
    ST_STRIKE       = 1 << 5,
    ST_DIM          = 1 << 6
} StyleFlags;

/****************
 * The 8+8 Colors
 ****************/
/*
typedef enum {
    BLACK           = 0,
    BLUE            = 1,
    GREEN           = 2,
    CYAN            = 3,
    RED             = 4,
    MAGENTA         = 5,
    BROWN           = 6,
    WHITE           = 7,
    BRIGHT_BLACK    = 8,
    BRIGHT_BLUE     = 9,
    BRIGHT_GREEN    = 10,
    BRIGHT_CYAN     = 11,
    BRIGHT_RED      = 12,
    BRIGHT_MAGENTA  = 13,
    BRIGHT_YELLOW   = 14,
    BRIGHT_WHITE    = 15 
} Color;
*/
typedef enum {
    BLACK           = 0,
    RED             = 1,
    GREEN           = 2,
    BROWN           = 3,
    BLUE            = 4,
    MAGENTA         = 5,
    CYAN            = 6,
    WHITE           = 7,
    BRIGHT_BLACK    = 8,
    BRIGHT_RED      = 9,
    BRIGHT_GREEN    = 10,
    BRIGHT_YELLOW   = 11,
    BRIGHT_BLUE     = 12,
    BRIGHT_MAGENTA  = 13,
    BRIGHT_CYAN     = 14,
    BRIGHT_WHITE    = 15
} Color;

/******************
 * System functions
 ******************/
void term_init(void);
void term_close(void);

/******************
 * Draw functions
 ******************/
void scr_init(void);
void scr_restore(void);
void scr_reset(void);
void scr_clear(void);
void scr_pt_char(int x, int y, char c);
void scr_pt_clr_char(int x, int y, uint8_t fg, uint8_t bg, char c);
void scr_pt(int x, int y, char *fstr,...);
void scr_pt_clr(int x, int y, uint8_t fg, uint8_t bg, char *fstr,...);
void scr_set_clr(uint8_t fg, uint8_t bg);
void scr_set_curs(int x, int y);
void scr_set_style(int style);

/*******************
 * Input functions
 *******************/
void kb_init(void);
void kb_restore(void);
char kb_get_char(void);
char* kb_get_str(int maxsz);
char* kb_get_str_at(int x, int y, int maxsz);

#endif // TERM_ENGINE_H
