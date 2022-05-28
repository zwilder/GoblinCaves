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
#ifndef GOBLINCAVES_H
#define GOBLINCAVES_H

/********
 * System 
 ********/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/***********************
 * Minor data structures
 ***********************/
#include <color.h>
#include <glyph.h>
#include <vec2i.h>
#include <rect.h>
#include <flags.h>
#include <tree.h>

/***********************
 * Major data structures
 ***********************/
/* Major Goal: Five (major) data types - structured like: Player, Enemy, Tile,
Effect, Pickup. */
#include <player.h>
#include <map.h>

/*********
 * Externs
 *********/
#include <externs.h>

/******
 * Core 
 ******/
#include <mt19937.h>
#include <game_engine.h>
#include <curses_engine.h>
#include <handle_events.h>
#include <update.h>
#include <draw.h>
#include <fov.h>

/**********
 * The rest
 **********/
#include <map_features.h>
#include <dungeons.h>
#include <log.h>

#endif
