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
void draw_screen(Glyph *screen);
void draw_str(int x, int y, char *str);
void draw_str_vec(Vec2i a, char *str);
void draw_colorstr(int x, int y, char *str, Color fg, Color bg);
void draw_colorstr_vec(Vec2i a, char *str, Color fg, Color bg);
void draw_hline(int x, int y, int w, Color color);
void draw_hline_vec(Vec2i a, int w, Color color);
void draw_vline(int x, int y, int h, Color color);
void draw_vline_vec(Vec2i a, int h, Color color);
void draw_solid_box(int x, int y, int w, int h, Color color);
void draw_solid_box_vec(Vec2i a, Vec2i d, Color color);
void draw_box(int x, int y, int w, int h, Color color);
void draw_box_vec(Vec2i a, Vec2i d, Color color);
void draw_msg_box(char *msg, Color fg, Color bg);
bool draw_yn_prompt(char *prompt, Color fg, Color bg);

/******************
 * draw_game.c functions
 ******************/
void draw_game(void);
void draw_hud(void);
void draw_msg(void);
Vec2i get_camera(void);
void draw_msg_log(void);
void draw_gameover(void);

/* Old function, possibly not needed? */
Glyph* create_full_screen(void);
#endif
