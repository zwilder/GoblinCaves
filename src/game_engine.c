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

StateFlags g_gamestate = ST_MENU;

void engine_init(void) {
    start_log();
    g_gamestate = ST_MENU;
    init_screenbuf();
    engine_draw();
}

void engine_run(void) {
    /* Enter main loop */
    int events;
    bool running = true;
    //double start = time(NULL)* 1000; //Start time in ms
    while(running) {
        //start = time(NULL) * 1000;
        /* Handle Events */
        events = handle_events();
        if(check_flag(events, EV_QUIT)) {
            running = false;
        }
        /* update */
        events = update(events);
        /* draw */
        engine_draw();
        /* 16ms is ~60fps, time(NULL) * 1000 is time in ms */
        //sleep((start + 16 - (time(NULL) * 1000))/1000);
    }
}

void engine_draw(void) {
    switch(g_gamestate) {
        case ST_GAME: draw_game(); break;
        case ST_MENU: draw_art(ART_TITLE); break;
        case ST_HELP: draw_art(ART_HELP); break;
        case ST_NWPL: draw_newpl(); break;
        case ST_LOG:  draw_msg_log(); break;
        case ST_GAMEOVER: draw_gameover(); break;
        case ST_INV: break;
        default: break;
    }
}

int get_input(void) {
    int input = (int)kb_get_char();
    if(input == 27) {
        // Esc code entered, read next two chars on buffer
        // Not the most elegant solution, but it works?
        input = kb_get_char(); // '['
        input = kb_get_char(); // The escape code
        switch(input) {
            case 'A': input = 'k'; break; // Up arrow
            case 'B': input = 'j'; break; // Down arrow
            case 'C': input = 'l'; break; // Right arrow
            case 'D': input = 'h'; break; // Left arrow
            default: break;
        }
    }
    return input;
}

void new_game(void) {
    if(g_player) {
        destroy_player();
    }
    if(g_maphead) {
        destroy_map(&g_maphead);
    }
    destroy_msglist(&g_msghead);
    destroy_msglist(&g_msgloghead);
    g_maphead = create_map(NULL);
    g_mapcur = g_maphead;
    g_mlist = NULL;
    g_player = create_player(&(g_mlist));
    g_tilemap = g_maphead->tiles;
    build_dungeon();

    update_fov();
}

void engine_close(void) {
    destroy_map(&g_maphead);
    destroy_mlist(&g_mlist);
    destroy_msglist(&g_msghead);
    destroy_msglist(&g_msgloghead);
    free(g_screenbuf);
}

/* integer to string functions from K&R C Book */
void kr_itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0) {  /* record sign */
        n = -n;          /* make n positive */
    }
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    kr_reverse(s);
}

void kr_reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

