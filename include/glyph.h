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
#ifndef GLYPH_H
#define GLYPH_H

/***********************
 * Minor data structures
 ***********************/
typedef struct {
    char ch;
    int fg;
    int bg;
} Glyph;

Glyph make_glyph(char ch, int fg, int bg);

Glyph* create_screen(void);
void set_screen_glyph_at(Glyph *screen, Vec2i pos, Glyph glyph);
void set_xy_screen_glyph(Glyph *screen, int x, int y, Glyph glyph);
void set_screen_str_at(Glyph *screen, Vec2i pos, char *str, int fg, int bg);
void set_xy_screen_str(Glyph *screen, int x, int y, char *str, int fg, int bg);
void destroy_screen(Glyph *screen);
void clear_screen(Glyph *screen);
int get_screen_index(int x, int y);

#endif
