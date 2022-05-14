#include <goblincaves.h>

bool curses_setup(void) {
    bool success = false;
    int bg_color = COLOR_BLACK;

    initscr();
    noecho();
    curs_set(0);
    cbreak();

    if(has_colors()) {
        success = true;
        start_color();
        /* Prepare the color pairs */
		/* PAIR_WHITE (pair 0) is *always* WHITE on BLACK */
		init_pair(PAIR_RED, COLOR_RED, bg_color);
		init_pair(PAIR_GREEN, COLOR_GREEN, bg_color);
		init_pair(PAIR_YELLOW, COLOR_YELLOW, bg_color);
		init_pair(PAIR_BLUE, COLOR_BLUE, bg_color);
		init_pair(PAIR_MAGENTA, COLOR_MAGENTA, bg_color);
		init_pair(PAIR_CYAN, COLOR_CYAN, bg_color);
		init_pair(PAIR_BLACK, COLOR_BLACK, bg_color);

		/* These pairs are used for drawing solid walls */
		init_pair(PAIR_WHITE_WHITE, COLOR_WHITE, COLOR_WHITE);
		init_pair(PAIR_RED_RED, COLOR_RED, COLOR_RED);
		init_pair(PAIR_GREEN_GREEN, COLOR_GREEN, COLOR_GREEN);
		init_pair(PAIR_YELLOW_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
		init_pair(PAIR_BLUE_BLUE, COLOR_BLUE, COLOR_BLUE);
		init_pair(PAIR_MAGENTA_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
		init_pair(PAIR_CYAN_CYAN, COLOR_CYAN, COLOR_CYAN);
		init_pair(PAIR_BLACK_BLACK, COLOR_BLACK, COLOR_BLACK);
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
            mvaddch(y, x, g_screen[index].ch | COLOR_PAIR(g_screen[index].color));
        }
    }
}

void curses_close(void) {
    /* Stupid function for now, but there may be other cleanup added later */
    endwin();
}
