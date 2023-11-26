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

int g_events = 0;

int handle_events(void) {
    int events = g_events;
    g_events = EV_NONE;
    if(g_gamestate == ST_GAME) {
        /* This loop is the money right here. The GC update loop should look
         * something like this:
         * Loop through the animation list, play animations in order
         * (wishlist item)
         * Loop through the monster list
         * If the monster is on the current level then...
         * - Can take turn? do it. Cant? gain energy
         */
        /* Each loop:
         * Wait for player input (handle_events)
         * Loop through all monsters UNTIL player can take turn (update)
         *   - if can take turn
         *      - Call appropriate update routine
         *      - Deduct energy if turn was successful
         *   - if cant take turn
         *      - Grant energy
         * Draw the screen.
         */
        while(!check_flag(events, EV_PLAYER_KP)) {
            events |= handle_keyboard(get_input());
        }
    } else if (g_gamestate == ST_NWPL) {
        events |= handle_keyboard(0);
    } else {
        events |= handle_keyboard(get_input());
    }
    return events;
}

int handle_keyboard(int input) {
    int output = EV_NONE;
    switch(g_gamestate) {
        case ST_MENU:
            output = handle_keyboard_menu(input);
            break;
        case ST_HELP:
            output = handle_keyboard_help(input);
            break;
        case ST_GAME:
            output = handle_keyboard_game(input);
            break;
        case ST_NWPL:
            output = handle_keyboard_newpl(input);
            break;
        case ST_LOG:
            output = handle_keyboard_log(input);
            break;
        case ST_GAMEOVER:
            output = handle_keyboard_gameover(input);
            break;
        default: break;
    }
    return output;
}

int handle_keyboard_log(int input) {
    int output = EV_NONE;
    if(input) {
        output = EV_CHST_GAME;
    }
    return output;
}

int handle_keyboard_menu(int input) {
    int output = EV_NONE; 
    switch(input) {
        case 'a':
            new_game();
            output = EV_CHST_NWPL;
            break;
        case 'b':
            /*output = EV_CHST_GAME;*/
            output = load_game();
            break;
        case 'c':
            /* High scores */
            break;
        case 'd':
            output = EV_QUIT;
            break;
        default: break;
    }
    return output;
}

char* get_player_name(void) {
    int maxlength = 33;
    scr_set_clr(BRIGHT_WHITE, BLACK);
    scr_set_style(ST_BOLD);
    char *str = kb_get_str_at((g_screenW/2) - (strlen("What is your name, adventurer? ")/2) + 2,
                        (g_screenH/2) + 1,
                         maxlength);

    return str;
}

char* get_random_name(void) {
    /* Display a menu with a list of markov chain generated names for the player
     * to choose from. */
    char *result = NULL;
    int i = -1;
    int j = 0;
    SList *menu = NULL, *slit = NULL, *in = NULL, *tmp = NULL;
    bool waiting = true;
    in = slist_load_dataset(g_mfiles[mt_rand(0,MARKOV_NUM)],' ');
    tmp = slist_load_dataset(g_mfiles[mt_rand(0,MARKOV_NUM)],' ');
    slist_add(&in, &tmp);
    MHTable *ht = markov_generate_mht(in);
    while(waiting) {
        menu = create_slist("Select a random name:");
        slist_push(&menu,"(Any other key to return to name entry)");
        slist_push(&menu,"123456789*");
        for(j = 0; j < 9; j++) {
            slist_push_node(&menu, generate_random_word(ht,NULL));
        }
        slist_push(&menu, "Generate New Random Names");
        char c = draw_cmenu(menu,WHITE,BLACK,GREEN);
        switch(c) {
            case '1': i = 0; break;
            case '2': i = 1; break;
            case '3': i = 2; break;
            case '4': i = 3; break;
            case '5': i = 4; break;
            case '6': i = 5; break;
            case '7': i = 6; break;
            case '8': i = 7; break;
            case '9': i = 8; break;
            case '*':
                // Generate new names
                break;
            default:
                waiting = false;
                break;
        }
        if (i >= 0) {
            // Find result in names
            slit = slist_get_node(menu, i+3);// first 3 items in menu aren't names
            if(slit) {
                result = strdup(slit->data);
                waiting = false;
            }
        }
        i = -1;
        destroy_slist(&menu);
    }
    destroy_slist(&in);
    destroy_mhtable(ht);
    return result;
}

int handle_keyboard_newpl(int input){
    int output = input;
    char *str = NULL;
    while(!str) {
        str = get_player_name();
        if(!str) {
            str = get_random_name();
        }
    }
    output = EV_CHST_GAME;
    if(g_player->name) {
        free(g_player->name);
    }
    g_player->name = str;
    return output;
}

int handle_keyboard_help(int input) {
    int output = EV_NONE; 
    if(input) {
        output = EV_CHST_GAME;
    }
    return output;
}

int handle_keyboard_gameover(int input) {
    int output = EV_NONE;
    if(input) {
        switch(input) {
            case 'q': 
                output = EV_CHST_MENU;
                if(g_player) {
                    destroy_mlist_monster(&g_mlist, g_player);
                    g_player = NULL;
                }
                break;
            case 's':
                write_memorial();
                break;
            default: break;
        }
    }
    return output;
}

int handle_keyboard_game(int input) {
    int output = EV_NONE;
    Vec2i newPos = {g_player->pos.x, g_player->pos.y};
    switch(input) {
        case 'k':
            /* up */
            newPos.y--;
            output |= EV_PLAYER_KP;
            break;
        case 'j':
            /* down */
            newPos.y++;
            output |= EV_PLAYER_KP;
            break;
        case 'h':
            /* left */
            newPos.x--;
            output |= EV_PLAYER_KP;
            break;
        case 'l':
            /* right */
            newPos.x++;
            output |= EV_PLAYER_KP;
            break;
        case 'y':
            newPos.x--;
            newPos.y--;
            output |= EV_PLAYER_KP;
            break;
        case 'u':
            newPos.x++;
            newPos.y--;
            output |= EV_PLAYER_KP;
            break;
        case 'b':
            newPos.x--;
            newPos.y++;
            output |= EV_PLAYER_KP;
            break;
        case 'n':
            newPos.x++;
            newPos.y++;
            output |= EV_PLAYER_KP;
            break;
        case 'o':
            g_player->flags = engage_flag(g_player->flags, MF_OPENDOOR);
            output |= EV_PLAYER_KP;
            break;
        case 'c':
            g_player->flags = engage_flag(g_player->flags, MF_CLOSEDOOR);
            output |= EV_PLAYER_KP;
            break;
        case '>':
            g_player->flags = engage_flag(g_player->flags, MF_MVDNSTAIRS);
            output |= EV_PLAYER_KP;
            break;
        case '<':
            g_player->flags = engage_flag(g_player->flags, MF_MVUPSTAIRS);
            output |= EV_PLAYER_KP;
            break;
        case 'L':
            output |= EV_CHST_LOG | EV_PLAYER_KP;
            break;
        case 'S':
            if(draw_yn_prompt("Save and quit?", BLACK, WHITE)) {
                save_game();
                output |= EV_QUIT | EV_PLAYER_KP;
            }
            break;
        case '?':
            output |= EV_CHST_HELP | EV_PLAYER_KP;
            break;
        case 'q':
            if(draw_yn_prompt("Are you sure you want to quit?", BLACK, WHITE)) {
                output |= EV_QUIT | EV_PLAYER_KP; 
            }
            break;
        default:
            break;
    }
    if(!eq_vec(g_player->pos, newPos)) {
        g_player->dpos = newPos;
        g_player->flags = engage_flag(g_player->flags, MF_MOVE);
    }
    return output;
}

Vec2i get_direction(char* action_str) {
    Vec2i result = {0, 0};
    int msgsz = strlen(action_str) + strlen(": Which direction?") + 2;
    char *msg_str = malloc(sizeof(char) * msgsz);
    int input = '\0';
    snprintf(msg_str, msgsz, "%s: Which direction?", action_str);
    draw_msg_box(msg_str, BLACK, WHITE);
    draw_screen(g_screenbuf);
    while((input = get_input()) == '\0') {
        // Wait for input
    }
    switch(input) {
        case 'y':
            result.y--;
            result.x--;
            break;
        case 'u':
            result.y--;
            result.x++;
            break;
        case 'b':
            result.y++;
            result.x--;
            break;
        case 'n':
            result.y++;
            result.x++;
            break;
        case 'k':
            result.y--;
            break;
        case 'j':
            result.y++;
            break;
        case 'h':
            result.x--;
            break;
        case 'l':
            result.x++;
            break;
        default:
            break;
    }
    free(msg_str);
    return result;
}
