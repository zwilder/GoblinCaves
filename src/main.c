#include <goblincaves.h>

int main(int argc, char* argv[]) {

    if(curses_setup()) {
        /* Start main loop */
        engine_init();
        engine_run();
        engine_close();
        mvprintw(20, 50, "Success!");
        getch();
        curses_close();
    } else {
        /* Print startup failed message */
        printf("Unable to start curses!\n");
    }
    return 0;
}
