#ifndef COLOR_H
#define COLOR_H

/*
 * Color definitions, borrowed from Angband, curses already has COLOR_RED, etc
 * defined internally, so this would heck with that if I were to rename it.
 * Mostly just trying to get things to work at this point (before making it
 * pretty) 
 */
/* from main-gcu.c */
#define PAIR_WHITE 0
#define PAIR_RED 1
#define PAIR_GREEN 2
#define PAIR_YELLOW 3
#define PAIR_BLUE 4
#define PAIR_MAGENTA 5
#define PAIR_CYAN 6
#define PAIR_BLACK 7
#define PAIR_WHITE_WHITE 8
#define PAIR_RED_RED 9
#define PAIR_GREEN_GREEN 10
#define PAIR_YELLOW_YELLOW 11
#define PAIR_BLUE_BLUE 12
#define PAIR_MAGENTA_MAGENTA 13
#define PAIR_CYAN_CYAN 14
#define PAIR_BLACK_BLACK 15


/*
 * From z-color.h
 * Angband "attributes" (with symbols, and base (R,G,B) codes)
 *
 * The "(R,G,B)" codes are given in "fourths" of the "maximal" value,
 * and should "gamma corrected" on most (non-Macintosh) machines.
 */

#define COLOUR_DARK     0  /* d */    /* 0 0 0 */
#define COLOUR_WHITE    1  /* w */    /* 4 4 4 */
#define COLOUR_SLATE    2  /* s */    /* 2 2 2 */
#define COLOUR_ORANGE   3  /* o */    /* 4 2 0 */
#define COLOUR_RED      4  /* r */    /* 3 0 0 */
#define COLOUR_GREEN    5  /* g */    /* 0 2 1 */
#define COLOUR_BLUE     6  /* b */    /* 0 0 4 */
#define COLOUR_UMBER    7  /* u */    /* 2 1 0 */
#define COLOUR_L_DARK   8  /* D */    /* 1 1 1 */
#define COLOUR_L_WHITE  9  /* W */    /* 3 3 3 */
#define COLOUR_L_PURPLE 10 /* P */    /* ? ? ? */
#define COLOUR_YELLOW   11 /* y */    /* 4 4 0 */
#define COLOUR_L_RED    12 /* R */    /* 4 0 0 */
#define COLOUR_L_GREEN  13 /* G */    /* 0 4 0 */
#define COLOUR_L_BLUE   14 /* B */    /* 0 4 4 */
#define COLOUR_L_UMBER  15 /* U */    /* 3 2 1 */

#define COLOUR_PURPLE      16    /* p */
#define COLOUR_VIOLET      17    /* v */
#define COLOUR_TEAL        18    /* t */
#define COLOUR_MUD         19    /* m */
#define COLOUR_L_YELLOW    20    /* Y */
#define COLOUR_MAGENTA     21    /* i */
#define COLOUR_L_TEAL      22    /* T */
#define COLOUR_L_VIOLET    23    /* V */
#define COLOUR_L_PINK      24    /* I */
#define COLOUR_MUSTARD     25    /* M */
#define COLOUR_BLUE_SLATE  26    /* z */
#define COLOUR_DEEP_L_BLUE 27    /* Z */
#define COLOUR_SHADE       28    /* for shaded backgrounds */

#endif
