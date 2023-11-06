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
 * An idea.
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
    /*curses_draw_msg is not the right function for doing this Zachary - go fix
     * yo'self - update, fixed myself, went down a rabbit hole while fixing this
     * function, realized I have a lot of other things to fix before I add in
     * the inventory... so this does absolutely nothing right now, and it should
     * be in draw_game.c */
    int x;
    draw_hline(0,0,SCREEN_WIDTH,WHITE);
    x = (SCREEN_WIDTH / 2) - (strlen("- Inventory -")/2);
    draw_colorstr(x,0,"- Inventory -", BLACK, WHITE);
}
