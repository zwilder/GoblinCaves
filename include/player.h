#ifndef PLAYER_H
#define PLAYER_H

typedef struct { 
    Vec2i pos;
    Vec2i dpos;
    Glyph glyph;
    int fovRadius;
} Player;

/********************
 * player.c functions
 ********************/
Player* create_player(Vec2i pos);
void destroy_player(void);


#endif 
