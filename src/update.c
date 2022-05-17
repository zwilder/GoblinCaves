#include <goblincaves.h>

int update(int events) {
    if(check_flag(events, EV_MOVE)) {
        player_move();
        events = remove_flag(events, EV_MOVE);
    }
    return events;
}

void player_move(void) {
    Vec2i dpos = g_player->dpos;
    int mapIndex = get_map_index(dpos.x,dpos.y);
    int dposMask = g_map[mapIndex].flags;
    /* Will check for entities at location here */
    /* Check tile at location */
    if(check_flag(dposMask, TF_BLK_MV)){
        /* Tile blocks movment, is it a door? */
        if(check_flag(dposMask, TF_CDOOR)) {
            /* Is door locked check will go here */
            open_door(dpos);
        }
    } else {
        /* Tile does not block movement */
        g_player->pos.y = g_player->dpos.y;
        g_player->pos.x = g_player->dpos.x;
        update_fov();
    }
}

void open_door(Vec2i pos) {
    int mapIndex = get_map_index(pos.x,pos.y);
    int mask = g_map[mapIndex].flags;
    mask = remove_flag(mask, TF_CDOOR | TF_BLK_MV | TF_BLK_LT);
    mask = engage_flag(mask, TF_ODOOR);
    g_map[mapIndex].flags = mask;
    g_map[mapIndex].glyph.ch = '_';
    update_fov();
}
