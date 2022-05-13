#include <goblincaves.h>

bool curses_setup(void) {
    bool success = false;
    initscr();
    noecho();
    curs_set(0);
    if(has_colors()) {
        success = true;
        /* Color init stuff here */
    } else {
        /* System does not support color, print error message */
        mvprintw(20, 50, "Your system does not support color, unable to start game!");
        getch();
    }
    return success;
}
