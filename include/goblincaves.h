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
