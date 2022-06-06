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

/* SREEN HEIGHT + GUI_HEIGHT + MSG_HEIGHT should equal 24, game screen should
 * fill standard term dimensions 80x24 */
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 20; 
const int GUI_HEIGHT = 2;
const int MSG_HEIGHT = 2; 

Glyph* create_screen(void) {
    Glyph *newScreen = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Glyph));
    int i;
    for(i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
        newScreen[i].ch = ' ';
        newScreen[i].fg = WHITE;
        newScreen[i].bg = BLACK;
    }

    return newScreen;
}

int get_screen_index(int x, int y) {
    return (x + (SCREEN_WIDTH * y));
}

Vec2i get_camera(void) {
    Vec2i camera;

    /* Get the camera */
    camera.x = g_player->pos.x - (SCREEN_WIDTH / 2);
    camera.y = g_player->pos.y - (SCREEN_HEIGHT / 2);

    /* Adjust the camera if the player is too close to the edge */
    if(g_player->pos.x < (SCREEN_WIDTH / 2)) {
        camera.x = 0;
    } else if (g_player->pos.x >= MAP_WIDTH - (SCREEN_WIDTH / 2)) {
        camera.x = 1 + MAP_WIDTH - SCREEN_WIDTH;
    } else {
        camera.x = g_player->pos.x - (SCREEN_WIDTH / 2);
    }

    if(g_player->pos.y < (SCREEN_HEIGHT / 2)) {
        camera.y = 0;
    } else if (g_player->pos.y >= MAP_HEIGHT - (SCREEN_HEIGHT / 2)) {
        camera.y = 1 + MAP_HEIGHT - SCREEN_HEIGHT;
    } else {
        camera.y = g_player->pos.y - (SCREEN_HEIGHT / 2);
    }

    return camera;
}
void draw_screen(void) {
    int i,x, y, index, mapIndex;
    MonsterList *monsters = g_mapcur->monsters;
    Vec2i screenpos, mappos;
    Vec2i camera = get_camera();

    Glyph *screen = create_screen();
    
    /* draw the map (tiles) on the screen */
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            mappos.x = x;
            mappos.y = y;
            screenpos = subtract_vec(mappos, camera);
            if(screenpos.x < 0 || screenpos.y < 0) {
                continue;
            }
            index = get_screen_index(screenpos.x, screenpos.y);
            mapIndex = get_map_index(x, y);
            if(index > (SCREEN_WIDTH * SCREEN_HEIGHT - 1) ||
               mapIndex > (MAP_WIDTH * MAP_HEIGHT - 1)) {
                /* Unsure why this is necessary, but draw_screen will cause
                 * segfaults without it */
                break;
            }
            if(is_visible(x,y)) {
                mark_explored(x,y);
                screen[index] = get_glyph_at(x,y);
            } else if(is_explored(x,y)) {
                screen[index] = get_glyph_at(x,y);
                if(check_flag(get_tflags_at(x,y), TF_BLK_MV) ||
                        check_flag(get_tflags_at(x,y), TF_UP) ||
                        check_flag(get_tflags_at(x,y), TF_DN)) {
                    screen[index].fg = BLUE;
                } else {
                    screen[index].fg = BLACK;
                }
                screen[index].bg = BLACK;
            }
        }
    }
    /* draw the pickups on the screen */
    
    /* draw the enemies on the screen */
    /*
    for(i = 0; i < count_mlist(monsters); i++) {
        if(monsters[i].data) {
            mappos.x = monsters[i].data->pos.x;
            mappos.y = monsters[i].data->pos.y;
            if(is_visible(mappos.x,mappos.y)) {
                screenpos = subtract_vec(mappos, camera);
                index = get_screen_index(screenpos.x,screenpos.y);
                screen[index] = monsters[i].data->glyph;
            }
        }
    }
    */


    /* draw the player on the screen */
    if(g_player) {
        set_screen_glyph_at(screen, subtract_vec(g_player->pos, camera),
                            g_player->glyph);
    }

    for(x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            if(index > (SCREEN_WIDTH * SCREEN_HEIGHT - 1)) {
                break;
            }
            if(screen[index].ch != ' ') {
                curses_draw_main(x,y, screen[index]);
            }
        }
    }
    free(screen);
}

void draw_gui(void) {
    /* 
Player Name                                                             Depth:xx
HP: xxx/xxx    stat                                      St:xx Dx:xx Pe:xx Vi:xx 
                                                                               *
     * curses_draw_ui(int x, int uirow, char *msg)
     */
    char snum[5];
    char depth[12] = "Depth: -";
    char hpstr[12] = "HP: ";
    char statstr[24] = "St:";
    int lvl = (g_mapcur->lvl + 1) * 10;
    curses_draw_ui(0, 0, g_player->name);
    kr_itoa(lvl, snum);
    strcat(depth, snum);
    curses_draw_ui(SCREEN_WIDTH - strlen(depth),0, depth);

    /* Construct HP string */
    kr_itoa(g_player->curhp, snum);
    strcat(hpstr, snum);
    strcat(hpstr, "/");
    kr_itoa(get_max_hp(g_player), snum);
    strcat(hpstr, snum);
    curses_draw_ui(0,1, hpstr);

    /* Construct stat string */
    kr_itoa(g_player->str, snum);
    strcat(statstr, snum);
    strcat(statstr, " Dx:");
    kr_itoa(g_player->dex, snum);
    strcat(statstr, snum);
    strcat(statstr, " Pe:");
    kr_itoa(g_player->per, snum);
    strcat(statstr, snum);
    strcat(statstr, " Vi:");
    kr_itoa(g_player->vit, snum);
    strcat(statstr, snum);
    curses_draw_ui(SCREEN_WIDTH - strlen(statstr),1,statstr);

    /*
    curses_draw_ui(0, 1, "HP: xxx/xxx    stat                                      St:xx Dx:xx Pe:xx Vi:xx");
    */

}

void draw_msg(void) {
    /*
     * Check g_msghead for msgs
     * count messages
     * while i < count
     *  - Pop off top msg
     *  - check length of top msg
     *    - If length greater than SCREEN_WIDTH, split lines
     *  - draw top msg on the first two lines of the screen
     *  - i++
     *  -if(i > 1) display [More - any key]
     */
    char *msg;
    int i = 0;
    int msgcount = count_msg(&g_msghead);
    while(i < msgcount) {
        msg = pop_msg(&g_msghead);
        curses_draw_msg(0,i,msg);
        push_msg(&g_msgloghead, msg);
        free(msg); /* Messy? */
        i++;
    }

}

void draw_msg_log(void) {
    int msgcount;
    int i = 0;
    int contx = (SCREEN_WIDTH / 2) - (strlen("[Press any key to continue]")/2);
    Msg *cur = g_msgloghead;
    cull_msg(&g_msgloghead);
    msgcount = count_msg(&g_msgloghead);
    setcolor(BLACK, WHITE);
    curses_draw_titlebar("Message Log", BLACK, WHITE);
    unsetcolor(BLACK, WHITE);
    while (i < msgcount) {
        curses_draw_msg(0,i+1, cur->str);
        i++;
        cur = cur->next;
    }
    curses_draw_msg(contx, i+2, "[Press any key to continue]");
}

void set_screen_glyph_at(Glyph *screen, Vec2i pos, Glyph glyph) {
    int index = get_screen_index(pos.x,pos.y);
    screen[index] = glyph;
}

void clear_screen(Glyph *screen) {
    int x, y, index;
    for (x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < SCREEN_HEIGHT; y++) {
            index = get_screen_index(x,y);
            screen[index].ch = ' ';
            screen[index].fg = WHITE;
            screen[index].bg = BLACK;
        }
    }
}

void destroy_screen(Glyph *screen) {
    if(NULL != screen) {
        free(screen);
    }
}
