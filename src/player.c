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

Player* create_player(Vec2i pos) {
    Player* newPlayer = malloc(sizeof(Player));

    newPlayer->pos.y = pos.y;
    newPlayer->pos.x = pos.x;

    newPlayer->dpos.y = pos.y;
    newPlayer->dpos.x = pos.x;

    newPlayer->glyph.ch = '@';
    newPlayer->glyph.fg = BRIGHT_WHITE; 
    newPlayer->glyph.bg = BLACK;

    newPlayer->str = mt_rand(5,10);
    newPlayer->dex = mt_rand(5,10);
    newPlayer->vit = mt_rand(5,10);
    newPlayer->per = mt_rand(5,10);

    newPlayer->curhp = get_max_hp(newPlayer);
    
    return newPlayer;
}

void destroy_player(void) {
    if(NULL != g_player) {
        free(g_player);
    }
}

void set_player_pos(Vec2i pos) {
    g_player->pos = pos;
    g_player->glyph.bg = get_glyphbg_at(pos.x,pos.y);
    update_fov();
}

/* If I do change these to be more generic, they should go in their own file,
 * "stats.c" or something. ORGANIZED. */
int get_fov(Player *player) {
    /* Just returning the perception, for now.
     * Might be useful to have this accept the perception/vitality as input then
     * calculate the FOV to return... for monsters and stuff? */
    return player->per;
}

int get_max_hp(Player *player) {
    /* Again, just winging this for now. AND AGAIN, might be better to accept
     * the vit/str inputs, then calculate and return the hp */
    return (player->vit + player->str) * 5;
}
