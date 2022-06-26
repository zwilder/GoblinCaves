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
#include <goblincaves.h>

int handle_events(void) {
    MList *tmp = NULL;
    int events = EV_NONE;
    switch(g_gamestate) {
        case ST_GAME:
            //if(check_flag(g_player->flags, MF_HAS_TURN)) {
                events = handle_keyboard(get_input());
            //}
            for(tmp = g_mlist; tmp; tmp = tmp->next) {
                if(!tmp) {
                    break; //for loops run at least once
                }
                if(tmp->data == g_player) {
                    continue; //Skip player
                } 
                if(tmp->data->locID == g_mapcur->lvl) {
                    // ONLY monsters on current level take turns
                    take_turn(tmp->data);
                }
            }
            break;
        default:
            events = handle_keyboard(get_input());
            break;
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

int handle_keyboard_newpl(int input){
    int output = EV_CHST_GAME;
    
    return output;
}
int handle_keyboard_help(int input) {
    int output = EV_NONE; 
    if(input) {
        output = EV_CHST_GAME;
    }
    return output;
}

int handle_keyboard_game(int input) {
    int output = EV_NONE;
    Vec2i newPos = {g_player->pos.x, g_player->pos.y};
    switch(input) {
        case KEY_UP:
        case 'k':
            /* up */
            newPos.y--;
            break;
        case KEY_DOWN:
        case 'j':
            /* down */
            newPos.y++;
            break;
        case KEY_LEFT:
        case 'h':
            /* left */
            newPos.x--;
            break;
        case KEY_RIGHT:
        case 'l':
            /* right */
            newPos.x++;
            break;
        case 'y':
            newPos.x--;
            newPos.y--;
            break;
        case 'u':
            newPos.x++;
            newPos.y--;
            break;
        case 'b':
            newPos.x--;
            newPos.y++;
            break;
        case 'n':
            newPos.x++;
            newPos.y++;
            break;
        case 'o':
            g_player->flags = engage_flag(g_player->flags, MF_OPENDOOR);
            break;
        case 'c':
            g_player->flags = engage_flag(g_player->flags, MF_CLOSEDOOR);
            break;
        case '>':
            g_player->flags = engage_flag(g_player->flags, MF_MVDNSTAIRS);
            break;
        case '<':
            g_player->flags = engage_flag(g_player->flags, MF_MVUPSTAIRS);
            break;
        case 'L':
            output = EV_CHST_LOG;
            break;
        case 'S':
            if(yn_prompt("Save and quit?", BLACK, WHITE)) {
                save_game();
                output = EV_QUIT;
            }
            break;
        case '?':
            output = EV_CHST_HELP;
            break;
        case 'q':
            if(yn_prompt("Are you sure you want to quit?", BLACK, WHITE)) {
                output = EV_QUIT; 
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
    char msg_str[32];
    strcpy(msg_str, action_str);
    strcat(msg_str, ": Which direction?");
    int input;
    msg_box(msg_str, BLACK, WHITE);
    input = get_input();
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

    return result;
}
