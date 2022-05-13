#include <goblincaves.h>

int main(int argc, char* argv[]) {

    if(curses_setup()) {
        /* Start main loop */
        mvprintw(20, 50, "Success!");
        getch();
    } else {
        /* Print startup failed message */
        printf("Unable to start curses!\n");
    }
    return 0;
}
