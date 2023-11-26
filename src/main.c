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
#include <unistd.h>
#include <ctype.h>
#include <goblincaves.h>

unsigned long kr_hash(char *s) {
    // String hash function from K&R, pg 144
    unsigned long hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval;
}

int main(int argc, char **argv) {
    int x,y;
    int c = 0;
    unsigned long seed = time(NULL);
    char *seedstr = strdup("Seeded with \"time(NULL)\"");
    // Process command line arguments
    opterr = 0; // Don't show default errors
    while((c = getopt(argc,argv,"vhts:")) != -1) {
        switch(c) {
            case 'v':
                //print version (someday)
                break;
            case 'h':
                //print help (someday)
                break;
            case 't':
                //use tiles (someday)
                break;
            case 's':
                // Seed prng with optarg
                seed = kr_hash(optarg);
                free(seedstr);
                seedstr = strdup(optarg);
                break;
            case '?':
                if (isprint(optopt)) {
                  fprintf(stderr, "Unkown option \'-%c\'\n", optopt);
                } else {
                  fprintf(stderr,
                          "Unkown option character \'\\x%x\'.\n",optopt);
                }
                break;
            default:
                break;
        }
    }

    // Initialize the psuedo random number generator
    init_genrand(seed);

    // Initialize the terminal drawing engine
    term_init();
    // For terminal emulators with transparency, this makes sure everything is
    // blacked out before drawing the screen
    for(x = 0; x < g_screenW; x++) {
        for(y = 0; y < g_screenH; y++) {
            scr_pt_clr_char(x,y,WHITE,BLACK,' ');
        }
    }

    // Start the game, and run it
    engine_init();
    write_log("Seed: %s",seedstr);
    free(seedstr);
    engine_run();

    // Cleanup
    engine_close();
    term_close();
    return 0;
}
