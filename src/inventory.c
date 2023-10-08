/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022-2023
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

/* 
...............................................................................
.                              - Inventory -
. A) Head          : None
. B) Body          : Iron Studded Armor
. C) Left Hand     : Iron Broadsword
. D) Right Hand    : None
. E) Gloves        : None
.
. Your pack contains the following:
. a)
. b)
. c)
. d)
. e)
. f)
. g)
. h)
.
.
.
. Select equipped item by pressing [A-E]
. Select pack item item by pressing [a-h]
. - Press [q] to close this screen -
...............................................................................
 */
void draw_inv(void) {
    curses_draw_titlebar("- Inventory -", WHITE, BLACK);

    /* For each of the following, the string will have a +
     * g_player->inv->slot.str or something added to it */
    curses_draw_msg(1,1, "A) Head       :");
    curses_draw_msg(1,2, "B) Body       :");
    curses_draw_msg(1,3, "C) Left Hand  :");
    curses_draw_msg(1,4, "D) Right Hand :");
    curses_draw_msg(1,5, "E) Gloves     :");

    curses_draw_msg(1,7, " Your pack contains the following:");
    curses_draw_msg(1,8, "a) ");
    curses_draw_msg(1,9, "b) ");
    curses_draw_msg(1,10, "c) ");
    curses_draw_msg(1,11, "d) ");
    curses_draw_msg(1,13, "e) ");
    curses_draw_msg(1,14, "f) ");
    curses_draw_msg(1,15, "g) ");
    curses_draw_msg(1,16, "h) ");

    curses_draw_msg(1,18, "Select equipped [A-E] or pack [a-h]");
   


 
    curses_draw_msg(1,23, "- Press [q] to close this screen -");
}
