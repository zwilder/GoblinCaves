#include <goblincaves.h>

Player* create_player(Vec2i pos) {
    Player* newPlayer = calloc(1, sizeof(Player));

    newPlayer->pos.y = pos.y;
    newPlayer->pos.x = pos.x;

    newPlayer->dpos.y = pos.y;
    newPlayer->dpos.x = pos.x;

    newPlayer->glyph.ch = '@';
    newPlayer->glyph.fg = BRIGHT_WHITE; 
    newPlayer->glyph.bg = BLACK;
    newPlayer->fovRadius = 10;
    
    return newPlayer;
}

void destroy_player(void) {
    if(NULL != g_player) {
        free(g_player);
    }
}
