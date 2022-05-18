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
        case 'q':
            output = EV_QUIT; 
        default:
            break;
    }
    g_player->dpos = newPos;
    return output;
}

Vec2i get_direction() {
    Vec2i result = {0, 0};
    int input;
    /* Temporary, need a better way to ask the player */
    msg_box("In which direction?", BLACK, WHITE);
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
