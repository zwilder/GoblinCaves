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

Player* g_player;

void engine_init(void) {
    start_log();
    g_player = create_player(make_vec(1,1));

    g_maphead = create_map(NULL);
    g_mapcur = g_maphead;
    g_tilemap = g_maphead->tiles;
    build_dungeon();

    update_fov();
    draw_screen();
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
        erase(); /* Curses call, will need to be fixed if I add graphics */
        draw_screen();
        refresh();
    }
}

int get_input(void) {
    /* Design goal: don't tie engine to curses.
     * SO - this stupid wrapper function MAY eventually check to see which
     * engine is running, use that engine to get/interpret the keypress, and
     * then return the result */
    int result = getch();
    return result;
}

void engine_close(void) {
    destroy_player();
    destroy_map(&g_maphead);
}

/* Random numbers from mt19937 generator */
int mt_rand(int min, int max) {
    return ((genrand_int32() % max) + min);
    /*
    return ((rand() % max) + min);
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
    return(chance <= result);
}

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

