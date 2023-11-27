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

char draw_cmenu(SList *menu, Color fg, Color bg, Color boxcolor) {
    /* Draws a message box containing a prompt, with a list of options.
     * The slist passed to draw_menu (menu) should contain the following in
     * order:
     * - A prompt
     * - A message at the bottom of the window. Optional if the string in the
     *   slist node is "\0"
     * - A list of characters to represent the option choices, for example,
     *   "abcd" will show each option as "[a] opt 1 [b] opt 2" etc. Optional if
     *   the string in the slist node is "\0", and if it isn't passed in than
     *   the options will be numbered sequentially.
     * - A list of options to be displayed to the user. 
     * The fg/bg colors are used for the text and the box around the menu. */

    int x,y,w,h,cx,cy,i;
    SList *slit = NULL, *slprompt = NULL, *slinstr = NULL;
    // First three item in menu are the prompt, instr, and optitems
    char *prompt = slist_get_node(menu, 0)->data;
    char *instr = slist_get_node(menu, 1)->data;
    char *optitems = slist_get_node(menu,2)->data;
    SList *options = slist_get_node(menu,3);
    char numstr[5] = "[1] ";
    char result = '\0';
    if(instr[0] == '\0') instr = NULL;
    if(optitems[0] == '\0') optitems = NULL;
    numstr[4] = '\0';
    w = (SCREEN_WIDTH * 2) / 3; // width is 2/3 screen width (66%)

    // Linewrap the prompt string
    slprompt = slist_linewrap(prompt,w);
    
    // Height is number of options + 2 for the border top/btm + number of lines
    // in prompt + 2 for space after prompt and before instr
    h = slist_count(slprompt) + 3 + slist_count(options); 
    if(instr) h += 1;

    // Linewrap the instr string
    if(instr) {
        slinstr = slist_linewrap(instr, w);
        h += slist_count(slinstr);
    }

    // x/y are centered on the screen
    x = (SCREEN_WIDTH / 2) - (w / 2) - 1;
    y = (SCREEN_HEIGHT / 2) - (h / 2);
    cx = x + 1;
    cy = y + 1;

    // Draw a box around the menu area
    draw_box(x-1,y-1,w+2,h+2,boxcolor,bg);

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
    cy++;

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
        cy++;
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

    // Returns screen to whatever it was before drawing the menu
    // (makes the screen flicker during new player creation, so disabling)
    //engine_draw();

    // Return input
    return result;
}

char draw_menu_basic(SList *menu) {
    return draw_cmenu(menu, WHITE, BLACK, WHITE);
}

char draw_menu(SList *menu, Color fg, Color bg) {
    return draw_cmenu(menu, fg, bg, fg);
}

char draw_menu_nobox(SList *menu, Color fg, Color bg) {
    return draw_cmenu(menu, fg ,bg, bg);
}
