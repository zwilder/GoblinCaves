#include <goblincaves.h>

int update(int events) {
    if(check_flag(events, EV_MOVE)) {
        player_move();
        events = remove_flag(events, EV_MOVE);
    }
    return events;
}

void player_move(void) {
    if(!(check_flag(g_map[get_map_index(g_player->dpos.x,g_player->dpos.y)].flags, TF_BLK_MV))){
        g_player->pos.y = g_player->dpos.y;
        g_player->pos.x = g_player->dpos.x;
        update_fov();
    }
}
