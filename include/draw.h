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
#ifndef DRAW_H
#define DRAW_H

/******************
 * draw.c functions
 ******************/
void init_screenbuf(void);
void draw_game(void);
void draw_gui(void);
void draw_msg(void);
void draw_msg_log(void);
void draw_gameover(void);
Vec2i get_camera(void);
Glyph* create_full_screen(void);

void draw_str(int x, int y, char *str);
void draw_str_vec(Vec2i a, char *str);
void draw_screenbuf(void);

#endif
