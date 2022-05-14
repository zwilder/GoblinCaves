#include <goblincaves.h>

Player* g_player;

void engine_init(void) {
    Vec2i startPos = {1, 1};
    g_player = create_player(startPos);
    g_screen = create_screen();
    g_map = create_map();
    draw_screen();
}

void engine_run(void) {
    /* Enter main loop */
    bool running = true;
    int ch;
    int events;
    while(running) {
        ch = getch();
        events = handle_keyboard(ch);
        if(-1 == events) {
            running = false;
        }
        /* update */
        /* draw */
        draw_screen();
    }
}

void engine_close(void) {
    destroy_player();
    destroy_map();
    destroy_screen();
}
