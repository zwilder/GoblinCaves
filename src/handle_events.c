#include <goblincaves.h>

int handle_keyboard(int input) {
    int output = EV_NONE;
    Vec2i newPos = {g_player->pos.x, g_player->pos.y};
    switch(input) {
        case 'k':
            /* up */
            newPos.y--;
            output = EV_MOVE;
            break;
        case 'j':
            /* down */
            newPos.y++;
            output = EV_MOVE;
            break;
        case 'h':
            /* left */
            newPos.x--;
            output = EV_MOVE;
            break;
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
