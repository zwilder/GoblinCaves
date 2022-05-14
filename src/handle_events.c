#include <goblincaves.h>

int handle_keyboard(int input) {
    /* Output will contain and return event flags, eg QUIT_GAME,
     * OPEN_INVENTORY, etc */
    int output = 0;
    /* Position setting is temporary, what these keypresses should and will do
     * eventually is change the dX,dY of the player... then the update routine
     * will check if the dx,dy is blocked, if theres a creature there etc */
    Vec2i newPos = {g_player->pos.x, g_player->pos.y};
    switch(input) {
        case 'k':
            /* up */
            newPos.y--;
            break;
        case 'j':
            /* down */
            newPos.y++;
            break;
        case 'h':
            /* left */
            newPos.x--;
            break;
        case 'l':
            /* right */
            newPos.x++;
            break;
        case 'q':
            output = -1; /* Temporary */
        default:
            break;
    }
    g_player->pos.y = newPos.y;
    g_player->pos.x = newPos.x;
    return output;
}
