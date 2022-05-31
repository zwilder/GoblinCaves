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
void setcolor(int fg, int bg);
void unsetcolor(int fg, int bg);
void curses_draw(int x, int y, Glyph glyph);
void msg_box(char* msg, Color fg, Color bg);
void error_msg_box(char* msg, Color fg, Color bg);
bool yn_prompt(char* msg, Color fg, Color bg);
void draw_menu(void);
void draw_help(void);
void curses_close(void);

#endif
