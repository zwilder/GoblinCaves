#include <goblincaves.h>

Player* create_player(Vec2i pos) {
    Player* newPlayer = calloc(1, sizeof(Player));

    newPlayer->pos.y = pos.y;
    newPlayer->pos.x = pos.x;

    newPlayer->glyph.ch = '@';
    newPlayer->glyph.color = 0; /* Temporary */
    
    return newPlayer;
}

void destroy_player(void) {
    if(NULL != g_player) {
        free(g_player);
    }
}
