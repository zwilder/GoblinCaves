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

/*****
 * draw.c
 *
 * This file contains all the "drawing" functions. The game (should) draw
 * everything to the screen buffer (g_screenbuf), and then draw the screenbuf on
 * the screen by calling the appropriate backend calls (ncurses, SDL, whatev).
 *
 * Important - the drawing functions (str, hline, vline, etc) draw on the global
 * screen buffer, g_screenbuf. To actually display them,
 * draw_screen(g_screenbuf) should be called after drawing (and
 * clear_screen(g_screenbuf) called before if you want a blank slate). 
 *
 * The functions that draw the actual "game" screen are in draw_game.c, along
 * with the functions for drawing the message log and game over screen. 
 *****/

const int GUI_HEIGHT = 2;
const int MSG_HEIGHT = 2; 

Glyph *g_screenbuf = NULL;

void init_screenbuf(void) {
    int h = SCREEN_HEIGHT;
    int i;
    g_screenbuf = malloc(SCREEN_WIDTH * h * sizeof(Glyph));
    for(i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        g_screenbuf[i].ch = ' ';
        g_screenbuf[i].fg = BLACK;
        g_screenbuf[i].bg = BLACK;
    }
}

void draw_glyph(int x, int y, Glyph g) {
    /* Draw a glyph in the appropriate offset spot for the size of the user's
     * terminal screen */
    int dx = (g_screenW / 2) - (SCREEN_WIDTH / 2);
    int dy = (g_screenH / 2) - (SCREEN_HEIGHT / 2);
    if(g.fg >= BRIGHT_BLACK) {
        scr_set_style(ST_BOLD);
    } else {
        scr_set_style(ST_NONE);
    }
    scr_pt_clr_char(x+dx,y+dy,g.fg,g.bg,g.ch);
}

void draw_screen(Glyph *screen) {
    /* Take a standard array of Glyphs, length SCREEN_WIDTH x SCREEN_HEIGHT, and
     * render it on the screen. */
    int x, y,i;
    for(x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            i = get_screen_index(x,y);
            if(i > (SCREEN_WIDTH * SCREEN_HEIGHT - 1)) {
                break;
            }
            draw_glyph(x,y,screen[i]);
        }
    }
}

void draw_str(int x, int y, char *str) {
    /* Draws a string on the global buffer, white fg/black bg by default.*/
    if(!str) return;
    int i,j,k;
    k=0;
    for(i = x; i < x + strlen(str); i++) {
        j = get_screen_index(i,y);
        g_screenbuf[j].ch = str[k];
        g_screenbuf[j].fg = WHITE;
        g_screenbuf[j].bg = BLACK;
        k++;
    }
}

void draw_str_vec(Vec2i a, char *str) {
    draw_str(a.x,a.y,str); 
}

void draw_colorstr(int x, int y, char *str, Color fg, Color bg) {
    /* Draws a string in color on the global buffer. */
    if(!str) return;
    int i,j,k;
    k = 0;
    for(i = x; i < x + strlen(str); i++) {
        j = get_screen_index(i,y);
        g_screenbuf[j].ch = str[k];
        g_screenbuf[j].fg = fg;
        g_screenbuf[j].bg = bg;
        k++;
    }
}

void draw_colorstr_vec(Vec2i a, char *str, Color fg, Color bg) {
    draw_colorstr(a.x,a.y,str,fg,bg);
}

void draw_hline(int x, int y, int w, Color color) {
    /* Starting at x,y and advancing x w times, draw */
    if((x < 0) || (y < 0) || (w <=0 )) return;
    int i,j;
    for(i = x; i < (x+w); i++) {
        j = get_screen_index(i,y);
        g_screenbuf[j].ch = '.';
        g_screenbuf[j].fg = color;
        g_screenbuf[j].bg = color;
    }
}

void draw_hline_vec(Vec2i a, int w, Color color) {
    draw_hline(a.x,a.y,w,color);
}

void draw_vline(int x, int y, int h, Color color) {
    /* Starting at x,y and advancing y h times, draw */
    if((x < 0) || (y < 0) || (h <=0 )) return;
    int i,j;
    for(i = y; i < (y+h); i++) {
        j = get_screen_index(x,i);
        g_screenbuf[j].ch = '.';
        g_screenbuf[j].fg = color;
        g_screenbuf[j].bg = color;
    }
}

void draw_vline_vec(Vec2i a, int h, Color color) {
    draw_vline(a.x,a.y,h,color);
}

void draw_solid_box(int x, int y, int w, int h, Color color) {
    int i;
    for(i = y; i < (y + h); i++) {
        draw_hline(x,i,w,color);
    }
}

void draw_solid_box_vec(Vec2i a, Vec2i d, Color color) {
    draw_solid_box(a.x,a.y,d.x,d.y,color);
}

void draw_solid_box_rect(Rect a, Color color) {
    draw_solid_box_vec(a.pos,a.dim, color);
}

void draw_box(int x, int y, int w, int h, Color color) {
    draw_solid_box(x,y,w,h,color);
    draw_solid_box(x+1,y+1,w-2,h-2,BLACK); // Might need a global fg/bg color default
}

void draw_box_vec(Vec2i a, Vec2i d, Color color) {
    draw_box(a.x,a.y,d.x,d.y,color);
}

void draw_box_rect(Rect a, Color color) {
    draw_box_vec(a.pos, a.dim, color);
}

void draw_msg_box(char *msg, Color fg, Color bg) {
    /* Draw a message in a box at the center of the screen. */
    int maxw = (SCREEN_WIDTH * 2) / 3;
    int x,y,w,h,i;
    SList *lines = NULL, *slistit = NULL;
    if(strlen(msg) > maxw) {
        /* We need line wrapping */
        lines = slist_linewrap(msg, maxw);
        h = slist_count(lines) + 2;
        x = (SCREEN_WIDTH / 2) - (maxw / 2) - 1;
        y = (SCREEN_HEIGHT / 2) - (h / 2);
        draw_solid_box(x,y,maxw,h,bg);
        slistit = lines;
        i = 1;
        while(slistit) {
            draw_colorstr(x+1,y+i,slistit->data,fg,bg);
            i++;
            slistit = slistit->next;
        }
        destroy_slist(&lines);
    } else {
        /* No line wrapping needed */
        w = strlen(msg) + 2;
        x = (SCREEN_WIDTH / 2) - (strlen(msg) / 2) - 1;
        h = 3; 
        y = (SCREEN_HEIGHT / 2) - 1;
        draw_solid_box(x,y,w,h,bg);
        draw_colorstr(x+1,y+1,msg,fg,bg);
    }
}

bool draw_yn_prompt(char *prompt, Color fg, Color bg) {
    /* [y/n] */
    int msgsz = strlen(prompt) + 10; // " [y/n]\0"
    char *msg = malloc(sizeof(char) * msgsz);
    bool result = false, waiting = true;
    int input;
    snprintf(msg,msgsz,"%s [y/n]", prompt); 
    draw_msg_box(msg, fg, bg);
    draw_screen(g_screenbuf);
    while(waiting) {
        input = get_input();
        switch(input) {
            case 'Y':
            case 'y':
                result = true;
                waiting = false;
                break;
            case 'N':
            case 'n':
                result = false;
                waiting = false;
                break;
            default: break;
        }
    }
    engine_draw(); // Clears the prompt from the screen after input
    free(msg);
    return result;
}

char draw_menu(char *prompt, char *instr, char *optitems, SList *options, Color fg, Color bg) {
    /* Draws a message box containing a prompt, with a list of options.
     * Options are passed into the function as a SList, and presented to the
     * player as a list of numbered options 1-9 (* for more or any other key to
     * abort). The player presses a number and that character (1-9,*, or other)
     * is returned as a char*/
    SList *slit = NULL, *slprompt = NULL, *slinstr = NULL;
    int x,y,w,h,cx,cy,i;
    char numstr[5] = "[1] ";
    char result = '\0';
    numstr[4] = '\0';
    w = (SCREEN_WIDTH * 2) / 3; // width is 2/3 screen width (66%)
    slprompt = slist_linewrap(prompt,w);
    
    // Height is number of options + 2 for the border top/btm + number of lines in prompt
    h = slist_count(slprompt) + 2 + slist_count(options); 
    if(instr) {
        slinstr = slist_linewrap(instr, w);
        h += slist_count(slinstr);
    }
    // x/y are centered on the screen
    x = (SCREEN_WIDTH / 2) - (w / 2) - 1;
    y = (SCREEN_HEIGHT / 2) - (h / 2);
    cx = x + 1;
    cy = y + 1;
    // Draw a solid box
    draw_solid_box(x,y,w,h,bg);
    // Draw the prompt
    slit = slprompt;
    while(slit) {
        // Bold the foreground color if possible
        i = fg + 8;
        if(i > 15) i = fg;
        draw_colorstr(cx,cy,slit->data,i,bg);
        cy++;
        slit = slit->next;
    }
    destroy_slist(&slprompt);
    // Draw the options
    slit = options;
    if(optitems) {
        i = 0;
    } else {
        i='1';
    }
    while(slit) {
        draw_colorstr(cx+4,cy,slit->data,fg,bg);
        // "[1] " = 4 chars, 5 with null
        if(optitems) {
            numstr[1] = optitems[i];    
        } else {
            numstr[1] = i;
        }
        draw_colorstr(cx,cy,numstr,fg,bg);
        i++;
        cy++;
        if(i>'9') break; // Limited to nine options currently
        if(optitems) {
            if(i > strlen(optitems)) i = 0; // Shouldn't happen, but if it do
        }
        slit = slit->next;
    }

    // If instructions, draw them
    if(slinstr) {
        slit = slinstr;
        while(slit) {
            draw_colorstr(cx,cy,slit->data,fg,bg);
            cy++;
            slit = slit->next;
        }
        destroy_slist(&slinstr);
    }

    // Draw on the screen
    draw_screen(g_screenbuf);

    // Wait for input
    while(true) {
        result = get_input();
        if(result != '\0') break;
    }

    // Returns screen to normal
    engine_draw();

    // Return input
    return result;
}

/*****
 * Old stuff below
 *****/

Glyph* create_full_screen(void) {
    /* This function allocates memory for the array of glyphs that contain the
     * "screen" that is drawn to, then initializes the entire screen with blank
     * spaces (' ', white text/black background). It's slightly different than
     * create_screen(...) in glyph.c in that the Glyph* it returns includes the
     * extra space taken up by the GUI bars at the top and bottom of the game
     * screen. This is useful for the title screen, help screen, etc. 
     *
     * TODO: This function MIGHT be safe to delete, it was only used by
     * write_memorial() in log.c. When monsters are added back in (and the
     * player can actually die), I'll be able to see if the memorial log is
     * writing properly. Until then, this functions stays here.
     */ 
    int w,h,i;
    w = SCREEN_WIDTH;
    h = SCREEN_HEIGHT + GUI_HEIGHT + MSG_HEIGHT;
    Glyph *newScreen = malloc(w * h * sizeof(Glyph));
    for(i = 0; i < (w * h); i++) {
        newScreen[i].ch = ' ';
        newScreen[i].fg = WHITE;
        newScreen[i].bg = BLACK;
    }
    return newScreen;
}
