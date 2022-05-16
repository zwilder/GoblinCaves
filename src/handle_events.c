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
        case 'q':
            output = EV_QUIT; 
        default:
            break;
    }
    g_player->dpos = newPos;
    return output;
}
