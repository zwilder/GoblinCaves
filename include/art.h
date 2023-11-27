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
#ifndef ART_H
#define ART_H

typedef enum {
    ART_NONE        = 0,
    ART_TOMBSTONE,
    ART_HELLO_WORLD,
    ART_TITLE,
    ART_HELP,
    ART_NEWPL
} ART_TYPES;

void draw_art(int art);
void open_art(Glyph *screen, int id);
void process_art(Glyph *screen, SList *art);

int hex2d_to_int(char a, char b);
int hexchar_to_color(char c);

void draw_tombstone(Glyph *screen);
void draw_hello_world(Glyph *screen);
void draw_title_screen(Glyph *screen);

#endif // ART_H
