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
#ifndef CURSES_ENGINE_H
#define CURSES_ENGINE_H

/***************************
 * curses_engine.c functions
 ***************************/
bool curses_setup(void);
void curses_draw_main(int x, int y, Glyph glyph);
void curses_close(void);

/* Every one of the following functions needs to be removed and replaced with a
 * similar call in draw.c */
void curses_draw_msg(int x, int y, char *msg);
void draw_nwpl(void);

#endif
