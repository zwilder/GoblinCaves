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
#ifndef EXTERNS_H
#define EXTERNS_H

extern Monster *g_player; /* Player reference player.c */
extern Map *g_maphead; /* Reference to map list head (level 0) map.c */
extern Map *g_mapcur; /* Reference to current map map.c */
extern Tile *g_tilemap; /* Reference to current tilemap map.c */
extern Msg *g_msghead; /* Reference to message list head, msg.c */
extern Msg *g_msgloghead; /* Reference to message log head, msg.c */
extern MList *g_mlist; /* Reference to monster list mlist.c */
extern int g_events; /* Global events, handle_events.c */
extern Glyph *g_screenbuf; /* Screen buffer, draw.c */
extern char *g_mfiles[]; /* List of markov files for random names, markov_gen.c */

extern StateFlags g_gamestate; /* Simple int state flag game_engine.c */

extern const int SCREEN_WIDTH; /* glyph.c */
extern const int SCREEN_HEIGHT; /* glyph.c */
extern const int GUI_HEIGHT; /* draw.c */
extern const int MSG_HEIGHT; /* draw.c */
extern const int MAP_WIDTH; /* map.c */
extern const int MAP_HEIGHT; /* map.c */
extern const int MIN_ROOM_SIZE; /* map.c */
extern const int MAX_ROOM_SIZE; /* map.c */
extern const int MIN_NUM_ROOMS; /* map.c */
extern const int MAX_NUM_ROOMS; /* map.c */
extern const int MAX_MONSTERS; /* map.c */
extern const int MARKOV_NUM; /* markov_gen.c */

#endif
