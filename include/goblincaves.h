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
#ifndef GOBLINCAVES_H
#define GOBLINCAVES_H

/********
 * System 
 ********/
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

/***********************
 * Minor data structures
 ***********************/
#include <toolbox.h>
#include <term_engine.h>
#include <flags.h>
#include <msg.h>

/***********************
 * Major data structures
 ***********************/
/* Four major data types - Monster, Effects, Tiles, Pickups */
#include <monster.h>
#include <mlist.h>
#include <map.h>

/*********
 * Externs
 *********/
#include <externs.h>

/******
 * Core 
 ******/
#include <game_engine.h>
#include <handle_events.h>
#include <update.h>
#include <draw.h>
#include <fov.h>
#include <save_load.h>
#include <inventory.h>

/**********
 * The rest
 **********/
#include <map_features.h>
#include <dungeons.h>
#include <log.h>
#include <pathfinding.h>
#include <art.h>
#include <markov.h>

#endif
