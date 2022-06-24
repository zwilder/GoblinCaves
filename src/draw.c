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
    int x, y, index, mapIndex;
    MList *tmp;
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
    
    /* draw the enemies on the screen, corpses first (they don't block movement) */
    tmp = g_mlist;
    while(tmp) {
        if(tmp->data->locID == g_mapcur->lvl) {
            mappos = tmp->data->pos;
            if(is_visible(mappos.x,mappos.y) && !is_alive(tmp->data)) {
                set_screen_glyph_at(screen, subtract_vec(mappos,camera),
                        tmp->data->glyph);
            }
        }
        tmp = tmp->next;
    }
    tmp = g_mlist;
    while(tmp) {
        if(tmp->data->locID == g_mapcur->lvl) {
            mappos = tmp->data->pos;
            if(is_visible(mappos.x,mappos.y) && is_alive(tmp->data)) {
                set_screen_glyph_at(screen, subtract_vec(mappos,camera),
                        tmp->data->glyph);
            }
        }
        tmp = tmp->next;
    }
    
    /* draw the player on the screen, so the player is on top of everything else */
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
    char *depth = malloc(40 * sizeof(char));
    char *hpstr = malloc(40 * sizeof(char));
    char *statstr = malloc(40 * sizeof(char));
    int lvl = (g_mapcur->lvl + 1) * 10;
    curses_draw_ui(0, 0, g_player->name);
    snprintf(depth,40, "Depth: -%d", lvl);
    curses_draw_ui(SCREEN_WIDTH - strlen(depth),0, depth);

    snprintf(hpstr,40, "HP: %d/%d", g_player->curhp, get_max_hp(g_player));
    curses_draw_ui(0,1, hpstr);

    snprintf(statstr,40,"Spd:%d St:%d Dx:%d Pe:%d Vi:%d",
            g_player->spd, g_player->str, g_player->dex, 
            g_player->per, g_player->vit);
    curses_draw_ui(SCREEN_WIDTH - strlen(statstr),1,statstr);

    free(depth);
    free(hpstr);
    free(statstr);
}

void draw_msg(void) {
    SList *msgwords = NULL;
    SList *tmp = NULL;
    char *msg;
    int i = 0;
    int line = 0;
    int msgcount = count_msg(&g_msghead);
    while(i < msgcount) {
        msg = pop_msg_back(&g_msghead);
        //curses_draw_msg(0,i,msg);
        tmp = split_string(msg, ' ');
        if(!msgwords) {
            msgwords = tmp;
            tmp = NULL;
        } else {
            add_SList(&msgwords, &tmp);
            destroy_SList(&tmp);
        }
        push_msg(&g_msgloghead, msg);
        free(msg); 
        i++;
    }
    if(msgwords) {
        msg = malloc(sizeof(char) * 500); //Large buffer
        i = 0;
        tmp = msgwords;
        while(tmp) {
            if((line == 1) && ((i + tmp->length + 17) > 80)) {
                /* Display [More - any key] prompt,
                 * kinda hacky. */
                curses_draw_msg(0,line,msg);
                setcolor(BLACK, WHITE);
                curses_draw_msg(80 - 16, line, "[More - any key]");
                unsetcolor(BLACK, WHITE);
                draw_screen();
                draw_gui();
                get_input();
                memset(msg,' ',80);
                msg[81] = '\0';
                curses_draw_msg(0,0, msg);
                curses_draw_msg(0,1, msg);
                memset(msg,0,500);
                line = 0;
                i = 0;
            }
            if(((i + tmp->length) > 80)) {
                curses_draw_msg(0,line,msg);
                memset(msg,0,500);
                line++;
                i = 0;
            }
            i += snprintf(msg+i, 500 - i, "%s ",tmp->data);
            tmp = tmp->next;
            if(!tmp && (strlen(msg) > 0)) {
                curses_draw_msg(0,line,msg);
            }
        }
        free(msg);
    }
    destroy_SList(&msgwords);
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
