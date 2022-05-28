/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022
* 
* This file is a part of Goblin Caves
*
* Goblin Caves is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Goblin Caves is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Goblin Caves.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <goblincaves.h>

int main(int argc, char* argv[]) {

    if(curses_setup()) {
        init_genrand(time(NULL));
        srand(time(NULL));
        /* Start main loop */
        engine_init();
        engine_run();
        engine_close();

        /*
        msg_box("         Goodbye!      ", BLACK, WHITE);
        setcolor(BLACK, WHITE);
        mvprintw((LINES / 2) + 1,
                (COLS / 2) - 11,
                "[Press any key to exit]");
        mvprintw((LINES / 2) + 2,
                (COLS / 2) - 12,
                "                         ");
        unsetcolor(BLACK, WHITE);
        getch();
        */

        curses_close();
    } else {
        /* Print startup failed message */
        printf("Unable to start curses!\n");
    }
    return 0;
}
