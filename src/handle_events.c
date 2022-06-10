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
            output = EV_MOVE;
            break;
        case KEY_DOWN:
        case 'j':
            /* down */
            newPos.y++;
            output = EV_MOVE;
            break;
        case KEY_LEFT:
        case 'h':
            /* left */
            newPos.x--;
            output = EV_MOVE;
            break;
        case KEY_RIGHT:
        case 'l':
            /* right */
            newPos.x++;
            output = EV_MOVE;
            break;
        case 'y':
            newPos.x--;
            newPos.y--;
            output = EV_MOVE;
            break;
        case 'u':
            newPos.x++;
            newPos.y--;
            output = EV_MOVE;
            break;
        case 'b':
            newPos.x--;
            newPos.y++;
            output = EV_MOVE;
            break;
        case 'n':
            newPos.x++;
            newPos.y++;
            output = EV_MOVE;
            break;
        case 'o':
            output = EV_OPEN; 
            break;
        case 'c':
            output = EV_CLOSE;
            break;
        case '>':
            output = EV_DN;
            break;
        case '<':
            output = EV_UP;
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
            /*Temporary, should be EV_CHST_HELP or something */
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
    g_player->dpos = newPos;
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
