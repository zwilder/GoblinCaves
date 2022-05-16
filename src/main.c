#include <goblincaves.h>

int main(int argc, char* argv[]) {

    if(curses_setup()) {
        init_genrand(time(NULL));
        /* Start main loop */
        engine_init();
        engine_run();
        engine_close();

        msg_box(" Goodbye! ", BLACK, WHITE);
        getch();

        curses_close();
    } else {
        /* Print startup failed message */
        printf("Unable to start curses!\n");
    }
    return 0;
}
