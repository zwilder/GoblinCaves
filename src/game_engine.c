#include <goblincaves.h>

Player* g_player;

void engine_init(void) {
    start_log();
    Vec2i startPos = {1, 1};
    g_player = create_player(startPos);
    g_map = create_map();
    create_dungeon();
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
        clear(); /* Curses call, will need to be fixed if I add graphics */
        draw_screen();
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
    destroy_map();
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
