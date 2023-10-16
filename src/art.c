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
#include <goblincaves.h>

/* Collection of functions to draw ASCII art - this would be a FANTASTIC thing
 * to put in an external file to read in later. Shoot, doing this in code is
 * verbose. A script file could look something like:
name:tombstone
x,y,char,color_foreground,color_background
...
;
 * Which would allow for things to be easily modified without recompiling the
 * entire dang program (not that that takes any time, really).
 *
 * This file will probably contain the functions to read the .config files for
 * the art. 
 *
 * UPDATE: I wrote a small application "arttogc" that will read a script file
 * and then generate the hard coded art below. The code it generates is
 * excessive (very), but it works. Even better, I could just have it execute code
 * instead of writing the code to a file if the reading code was put here...
 * which will allow all art to just be read from a config file on demand - no
 * recompiling necessary and MAYBE even while the game is running! WILD. 
 */
void draw_art(int art) {
    /* This makes a screen, and draws art of ART_TYPE art on it */
    Glyph *screen = create_full_screen();
    int w,h;
    int x,y,index;
    w = SCREEN_WIDTH;
    h = SCREEN_HEIGHT + GUI_HEIGHT + MSG_HEIGHT;

    /*
    switch(art) {
        //case ART_TOMBSTONE: draw_tombstone(screen); break;
        case ART_TOMBSTONE: open_art(screen,ART_TITLE); break;
        case ART_HELLO_WORLD: draw_hello_world(screen); break;
        case ART_TITLE: draw_title_screen(screen); break;
        default: break;
    }
    */
    open_art(screen,art);

    for(x = 0; x < w; x++) {
        for(y = 0; y < h; y++) {
            index = get_screen_index(x,y);
            if(index > (w * h - 1)) {
                break;
            }
            if(screen[index].ch != ' ') {
                curses_draw_main(x,y-2, screen[index]);
            }
        }
    }
    free(screen);
}

void open_art(Glyph *screen, int id) {
    /* Opens the gcart.cfg file, searches for the art specified by id, and
     * draws it on the screen. */

    /* Might be "better" to have the SList for art as a global variable, so it
     * can be set once on game start*/
    char in;
    int i = 0;
    int numlines = 0;
    //char *instr = malloc(sizeof(char) * 567);
    char instr[567];
    /* Longest a string can be is 
     * id string !id:xx 6
     * CcFBXx (80 * 7) 
     * = 566 + 1 for null*/
    FILE *f = fopen("gcart.cfg","r+");
    SList *lines = NULL;
    SList *linesit = NULL; 
    SList *tmp = NULL;
    bool skip = false;
    if(!f) return;

    /* Read file, skip comments, store lines */
    in = fgetc(f);
    instr[i] = '\0';
    while(in != EOF) {
        if(in == '#') {
            skip = true;
        }
        if(in == '\n') {
            /* Reached end of a line, add it to the SList */
            instr[i] = '\0';
            if(!skip) {
                push_SList(&lines, instr);
            }
            i = 0;
            instr[i] = '\0';
            skip = false;
        } else {
            instr[i] = in;
            i++;
        }
        in = fgetc(f);
    }

    /* Find the first line of the correct id */
    linesit = lines;
    while(linesit) {
        if(linesit->data[0] == '!') {
            /* Found an id line, check if it's what we want */
            tmp = split_string(linesit->data, ':');
            if(atoi(tmp->next->data) == id) {
                /* Bingo, next line is the start of what we want */
                linesit = linesit->next;
                numlines = atoi(tmp->next->next->data);
                break;
            }
            destroy_SList(&tmp);
        }
        linesit = linesit->next;
    }

    /* If we found the id, proceed through lineit, adding strings to new slist
     * tmp until we read another !id line */
    if(linesit) {
        destroy_SList(&tmp);
        for(i = 0; i < numlines; i++) {
            push_SList(&tmp, linesit->data);
            linesit = linesit->next;
        }
        process_art(screen, tmp);
    }

    /* Release memory */
    destroy_SList(&lines);
    destroy_SList(&tmp);
    
    fclose(f);
}

void process_art(Glyph *screen, SList *art) {
    int x,y,c,fg,bg;
    SList *artit = NULL; 
    SList *yspl = NULL;
    SList *xspl = NULL;
    SList *xit = NULL;
    if(!art || !screen) return;
    artit = art;
    while(artit) {
        yspl = split_string(artit->data, ':');
        //write_log(yspl->data);
        if(yspl->next) {
            //write_log(yspl->next->data);
            y = atoi(yspl->data);
            xspl = split_string(yspl->next->data, ' ');
            xit = xspl;
            while(xit) {
                // CcFBXx 
                //write_log(xit->data);
                c = hex2d_to_int(xit->data[0], xit->data[1]);
                x = hex2d_to_int(xit->data[4], xit->data[5]);
                fg = hexchar_to_color(xit->data[2]);
                bg = hexchar_to_color(xit->data[3]);
                set_xy_screen_glyph(screen, x, y, make_glyph(c,fg,bg));
                xit = xit->next;
            }
            destroy_SList(&xspl);
        }
        destroy_SList(&yspl);
        artit = artit->next;
    }
}

int hex2d_to_int(char a, char b) {
    a = ((a <= '9') ? a - '0' : (a & 0x7) + 9);
    b = ((b <= '9') ? b - '0' : (b & 0x7) + 9);
    return (a << 4) + b;
}

int hexchar_to_color(char c) {
    switch(c) {
        case '0': return 0; break;
        case '1': return 1; break;
        case '2': return 2; break;
        case '3': return 3; break;
        case '4': return 4; break;
        case '5': return 5; break;
        case '6': return 6; break;
        case '7': return 7; break;
        case '8': return 8; break;
        case '9': return 9; break;
        case 'a':
        case 'A': return 10; break;
        case 'b':
        case 'B': return 11; break;
        case 'c':
        case 'C': return 12; break;
        case 'd':
        case 'D': return 13; break;
        case 'e':
        case 'E': return 14; break;
        case 'f': 
        case 'F': return 15; break;
        default: return 0; break;
    }
}

void draw_tombstone(Glyph *screen) {
    /*****

    ,    ,  \             _ooooooooooo_                                             
     ._,. \  \           =         ,  >=o                                           
    /  _ \_\__\         |          >O=% |:      Game Over!                          
    \(_ )/ /  /        |         `/%\    |                                          
    `._,' /  /        |______ ___________ |:    Press [q] to return to the main menu                                    
    /___\,`./         || ___ \_   _| ___ \|:          [t] to write a memorial file                              
    _____\,-'         || \_/ / | | | |_/ /|:                                        
         :\ `         ||    /  | | |  __/ |:                                        
         :            || |\ \ _| |_| |    |:                                        
         :            |\_| \_|\___/\_|    |:                                        
         ;            |                   |:                                        
         :            |      Griff        |:                                        
          :           |                   |:                                        
          :           |    Died 50ft      |:                                        
        / _ \         | below the surface |:  ,                                     
      \_\(X)/_/    oOOo     10/12/23      |: :,.                                    
       _//"\\_    oO`,Oo                  .;: ;                                     
        /   \      oOOo                   :`,'                                      
                    / |                   |`;                                       
                 \ |~~~~     ~~~~`        |:`p                                      
                 \\|//  ~ ~~~    ~~~~~ ~~~~~d,                                      
                                      ~      p                                      


    *****/
}
void draw_hello_world(Glyph *screen) {
    /*****
     __   __  _______  ___      ___      _______       
    |  | |  ||       ||   |    |   |    |       |      
    |  |_|  ||    ___||   |    |   |    |   _   |      
    |       ||   |___ |   |    |   |    |  | |  |      
    |       ||    ___||   |___ |   |___ |  |_|  |      
    |   _   ||   |___ |       ||       ||       |      
    |__| |__||_______||_______||_______||_______|      
     _     _  _______  ______    ___      ______   __  
    | | _ | ||       ||    _ |  |   |    |      | |  | 
    | || || ||   _   ||   | ||  |   |    |  _    ||  | 
    |       ||  | |  ||   |_||_ |   |    | | |   ||  | 
    |       ||  |_|  ||    __  ||   |___ | |_|   ||__| 
    |   _   ||       ||   |  | ||       ||       | __  
    |__| |__||_______||___|  |_||_______||______| |__| 
    *****/
}
void draw_title_screen(Glyph *screen) {
    /*****

            ____\   /__\|_____|   /_____\  /\/_________\   /______
                 \ /          |  /       \/             \ /      
             _______  _______ |/_____   _       ________\/_       
            (  ____ \(  ___  )(  ___ \ ( \      \__   __/( (    /|
            | (    \/| (   ) || (   ) )| (         ) (   |  \  ( |
            | |      | |   | || (__/ / | |         | |   |   \ | |
            | | ____ | |   | ||  __ (  | |         | |   | (\ \) |
            | | \_  )| |   | || (  \ \ | |         | |   | | \   |
            | (___) || (___) || )___) )| (____/\___) (___| )  \  |
            (_______)(_______)|/ \___/ (_______/\_______/|/    )_)
                (  ____ \(  ___  )|\     /|(  ____ \(  ____ \
                | (    \/| (   ) || )   ( || (    \/| (    \/       
                | |      | (___) || |   | || (__    | (_____        
                | |      |  ___  |( (   ) )|  __)   (_____  )       
                | |      | (   ) | \ \_/ / | (            ) |       
                | (____/\| )   ( |  \   /  | (____/\/\____) |       
                (_______/|/ /|  \|   \_/   (_______/\_______) /\
                /\         / |      /\               /\      /  \
            ___/  \___/ \_/  |_____/  \|\______/\___/  \____/    \
            [a] - New Adventure                   [c] High Scores
            [b] - Load Adventure                  [d] Quit

                        -- (c) Zach Wilder 2022-2023 --
    *****/
}
