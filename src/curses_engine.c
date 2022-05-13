#include <goblincaves.h>

bool curses_setup(void) {
    bool success = false;
    initscr();
    noecho();
    curs_set(0);
    cbreak();
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

void curses_draw(void) {
    int x,y,index;
    /* clear the screen - curses call */
    clear();
    /* Draw the screen on the terminal with curses */
    for (x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            mvaddch(y, x, g_screen[index].ch);
        }
    }
}

void curses_close(void) {
    /* Stupid function for now, but there may be other cleanup added later */
    endwin();
}
