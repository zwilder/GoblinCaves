#include <goblincaves.h>

bool curses_setup(void) {
    bool success = false;

    initscr();
    noecho();
    curs_set(0);
    cbreak();

    if(has_colors()) {
        success = true;
        start_color();
        init_colorpairs();
    } else {
        /* System does not support color, print error message */
        mvprintw(20, 50, "Your system does not support color, unable to start game!");
        getch();
    }
    return success;
}

void setcolor(int fg, int bg) {
    /* Set the color pair (colornum) and bold/bright (A_BOLD) */
    attron(COLOR_PAIR(colornum(fg,bg)));
    if(is_bold(fg)) {
        attron(A_BOLD);
    }
}

void unsetcolor(int fg, int bg) {
    /* Unset the color pair (colornum) and bold/bright (A_BOLD) */
    attroff(COLOR_PAIR(colornum(fg,bg)));
    if(is_bold(fg)) {
        attroff(A_BOLD);
    }
}

void curses_draw(void) {
    int x,y,index,fg,bg;
    int xoffset = COLS / 2; /* terminal center x */
    int yoffset = LINES / 2; /* terminal center y */

    xoffset -= SCREEN_WIDTH / 2;
    yoffset -= SCREEN_HEIGHT / 2;

    clear();

    /* Draw the screen on the terminal with curses */
    for (x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            /* Rewrite this to match ColorDemo */
            fg = g_screen[index].fg;
            bg = g_screen[index].bg;
            setcolor(fg,bg);
            mvaddch(y + yoffset, x + xoffset, g_screen[index].ch);
            unsetcolor(fg,bg);
        }
    }
}

void msg_box(char* msg, Color fg, Color bg) {
    /* Simple message box, displayed at the center of the screen. Will probably
     * need tweaking for fancy things like line wrapping, etc */
    int msglength = strlen(msg);
    int i,x,y;
    x = (COLS / 2) - (msglength / 2);
    y = (LINES / 2);
    setcolor(fg,bg);
    for(i = -1; i <= msglength; i++) {
        mvaddch(y - 1, x + i, ' ');
        mvaddch(y, x + i, ' ');
        mvaddch(y + 1, x + i, ' ');
    }
    mvprintw(y, x, msg);
    unsetcolor(fg,bg);
}

void curses_close(void) {
    /* Stupid function for now, but there may be other cleanup added later */
    endwin();
}
