#include <goblincaves.h>

Player* g_player;

void engine_init(void) {
    Vec2i startPos = {1, 1};
    g_player = create_player(startPos);
    g_screen = create_screen();
    g_map = create_map();
    draw_dungeon();
    update_fov();
    draw_screen();
}

void engine_run(void) {
    /* Enter main loop */
    int ch, events;
    bool running = true;
    while(running) {
        /* Handle Events */
        ch = getch();
        events = handle_keyboard(ch);
        if(check_flag(events, EV_QUIT)) {
            running = false;
        }
        /* update */
        events = update(events);
        /* draw */
        draw_screen();
    }
}

void engine_close(void) {
    destroy_player();
    destroy_map();
    destroy_screen();
}

/* Mostly unnecessary helper functions, but keeping them here as a reminder how
 * do */
bool check_flag(int mask, int flag) {
    /* Is flag on? */
    return((mask & flag) == flag);
}
int toggle_flag(int mask, int flag) {
    /* Toggles flag on/off */
    return(mask ^= flag);
}
int remove_flag(int mask, int flag) {
    /* Turns off flag */
    return(mask &= ~flag);
}
int engage_flag(int mask, int flag) {
    /* Turns on flag */
    return(mask |= flag);
}

/* Random numbers from mt19937 generator */
int mt_rand(int min, int max) {
    return ((int)(genrand_int32() % max + min));
}

bool mt_bool() {
    int result = mt_rand(0,10);
    return (result <= 5);
}
