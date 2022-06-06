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
    engine_draw();
}

void engine_run(void) {
    /* Enter main loop */
    int events;
    bool running = true;
    while(running) {
        /* Handle Events */
        events = handle_keyboard(get_input());
        if(check_flag(events, EV_QUIT)) {
            running = false;
        }
        /* update */
        events = update(events);
        /* draw */
        engine_draw();
    }
}

void engine_draw(void) {
    erase(); /* Curses call, will need to be fixed if I add graphics */
    switch(g_gamestate) {
        case ST_GAME:
            draw_msg();
            draw_screen();
            draw_gui();
            break;
        case ST_MENU:
            draw_menu();
            break;
        case ST_HELP:
            draw_help();
            break;
        case ST_NWPL:
            draw_nwpl();
            break;
        case ST_LOG:
            draw_msg_log();
            break;
        default:
            break;
    }
    refresh();
}

int get_input(void) {
    /* Design goal: don't tie engine to curses.
     * SO - this stupid wrapper function MAY eventually check to see which
     * engine is running, use that engine to get/interpret the keypress, and
     * then return the result */
    int result = 0;
    if(g_gamestate != ST_NWPL) {
        result = getch();
    }
    return result;
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
    g_player = create_player(make_vec(1,1));
    g_maphead = create_map(NULL);
    g_mapcur = g_maphead;
    g_tilemap = g_maphead->tiles;
    push_mlist(&(g_mapcur->monsters), g_player);
    /*
    g_mapcur->monsters = add_mlist_front(g_mapcur->monsters, g_player);
    */
    //build_dungeon();

    update_fov();
}

void engine_close(void) {
    /*destroy_map(&g_maphead);*/
    destroy_msglist(&g_msghead);
    destroy_msglist(&g_msgloghead);
}

/* Random numbers from mt19937 generator */
int mt_rand_lim(int limit) {
    /* So, the random number functions below with the % operator will introduce
     * skew. Like trying to split ten candies with 3 kids - and not being able
     * to cut anything into smaller pieces. A single piece will be left over...
     * This takes the candy, divides it by 3, and if the result is greater than
     * 3 puts it back into the bucket. */
    int divisor = RAND_MAX/(limit + 1);
    int retval;
    do {
        retval = genrand_int32() / divisor;
    } while (retval > limit);

    return retval;
}
int mt_rand(int min, int max) {
    return (mt_rand_lim(max - min) + min);
    /*return (genrand_int32() % (max - min + 1) + min);*/
    /*
    return ((rand() % (max - min + 1) + min);
    */
}

bool mt_bool() {
    int result = mt_rand(1,10);
    return (result <= 5);
}

bool mt_chance(int chance) {
    /* Idea: I want a 1/3 chance of something happening, so I call
     * mt_chance(33). It gets a random number between 1 and 100, and then
     * returns true if the random number is less than the 33. */
    int result = mt_rand(1,100);
    return(result <= chance);
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

