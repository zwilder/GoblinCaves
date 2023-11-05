/*
* Goblin Caves
* Copyright (C) Zach Wilder 2022-2023
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

void draw_game(void) {
    int x,y, i, mapIndex, tflags;
    MList *mlistit;
    Vec2i screenpos, mappos;
    Vec2i camera = get_camera();
    
    // Clear the screen buffer
    //clear_screenbuf();
    clear_screen(g_screenbuf);
    
    /* Draw the map tiles on the buffer */
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            mappos.x = x;
            mappos.y = y;
            
            // Subtract camera position from map position to get screen position
            screenpos = subtract_vec(mappos, camera);
            if((screenpos.x < 0) || (screenpos.y < 0)) {
                //If something is outside the range, continue
                continue;
            }
            
            // index in g_screenbuf
            i = get_screen_index(screenpos.x, screenpos.y);

            // index in g_tilemap
            mapIndex = get_map_index(x, y);
            if((i > (SCREEN_WIDTH * SCREEN_HEIGHT - 1)) ||
               (mapIndex > (MAP_WIDTH * MAP_HEIGHT - 1))) {
                //if either are out of bounds, break loop
                break;
            }

            if(is_visible(x,y)) {
                mark_explored(x,y);
                g_screenbuf[i] = get_glyph_at(x,y);
            } else if(is_explored(x,y)) {
                g_screenbuf[i] = get_glyph_at(x,y);
                tflags = get_tflags_at(x,y);
                if(check_flag(tflags, TF_BLK_MV) || check_flag(tflags, TF_UP) ||
                        check_flag(tflags, TF_DN)) {
                    g_screenbuf[i].fg = BLUE;
                } else {
                    g_screenbuf[i].fg = BLACK;
                }
                g_screenbuf[i].bg = BLACK;
            }
        }
    }
    /* draw the pickups on the buffer */
    
    /* draw the enemies on the buffer, corpses first (they don't block movement) */
    mlistit = g_mlist;
    while(mlistit) {
        if(mlistit->data->locID == g_mapcur->lvl) {
            mappos = mlistit->data->pos;
            if(is_visible(mappos.x,mappos.y) && !is_alive(mlistit->data)) {
                set_screen_glyph_at(g_screenbuf, subtract_vec(mappos,camera),
                        mlistit->data->glyph);
            }
        }
        mlistit = mlistit->next;
    }
    mlistit = g_mlist;
    while(mlistit) {
        if(mlistit->data->locID == g_mapcur->lvl) {
            mappos = mlistit->data->pos;
            if(is_visible(mappos.x,mappos.y) && is_alive(mlistit->data)) {
                set_screen_glyph_at(g_screenbuf, subtract_vec(mappos,camera),
                        mlistit->data->glyph);
            }
        }
        mlistit = mlistit->next;
    }

    /* draw the player on the buffer, so the player is on top of everything else */
    if(g_player) {
        set_screen_glyph_at(g_screenbuf, subtract_vec(g_player->pos, camera),
                            g_player->glyph);
    }

    /* Draw the Message buffer - Temporarily bright 0s to get drawing sorted */
    for(x = 0; x < SCREEN_WIDTH; x++) {
        for(y = 0; y < MSG_HEIGHT; y++) {
            i = get_screen_index(x,y);
            g_screenbuf[i].ch = ' ';
            g_screenbuf[i].fg = WHITE;
            g_screenbuf[i].bg = BLACK;
        }
    }
    /* Draw the GUI (HUD) */
    draw_hud();
    
    /* Draw the screen buffer */
    draw_screen(g_screenbuf);
}

void draw_hud(void) {
    /* 
     * This function constructs the following strings:
     
Player Name                                                             Depth:xx
HP: xxx/xxx    stat                                      St:xx Dx:xx Pe:xx Vi:xx 
                                                                               
     * and then draws them to the screen buffer.
     */
    char *depth = malloc(40 * sizeof(char));
    char *hpstr = malloc(40 * sizeof(char));
    char *statstr = malloc(40 * sizeof(char));
    int lvl = (g_mapcur->lvl + 1) * 10;
    int y;
    snprintf(depth,40, "Depth: -%d", lvl);
    snprintf(hpstr,40, "HP: %d/%d", g_player->curhp, get_max_hp(g_player));
    snprintf(statstr,40,"Spd:%d St:%d Dx:%d Pe:%d Vi:%d",
            g_player->spd, g_player->str, g_player->dex, 
            g_player->per, g_player->vit);
    
    // Draw on Buffer
    y = SCREEN_HEIGHT - GUI_HEIGHT;
    draw_str(0,y, g_player->name);
    draw_str(SCREEN_WIDTH - strlen(depth), y, depth);
    y++; //Next line
    draw_str(0,y, hpstr);
    draw_str(SCREEN_WIDTH - strlen(statstr),y, statstr);
    free(depth);
    free(hpstr);
    free(statstr);
}

void draw_msg(void) {
    /* This function loops through the messages list, clearing entries by:
     *
     * 1) Clearing (popping) the message in the global linked list
     * 2) Adding it to a string (msg)
     * 3) Pushing the message into the message log linked list.
     * 4) Drawing the messages to the top of the screen by calling
     *    curses_draw_msg(...)
     *
     * TODO: This function breaks design. It should only DRAW the messages, not
     * update the messages at the same time. There needs to be a function added
     * to update the message list. 
     */
    SList *msgwords = NULL;
    SList *tmp = NULL;
    char *msg;
    int i = 0;
    int line = 0;
    int msgcount = count_msg(&g_msghead);
    while(i < msgcount) {
        msg = pop_msg_back(&g_msghead);
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
            if((line == 1) && ((i + tmp->length + 7) > 80)) {
                curses_draw_msg(0,line,msg);
                setcolor(BLACK, WHITE);
                curses_draw_msg(80 - 7, line, "[More]");
                unsetcolor(BLACK, WHITE);
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

Vec2i get_camera(void) {
    /* This nifty function allows the map where the player is to be bigger than
     * the screen. It finds and returns a "camera" which is just a set of
     * x,y coordinates that centers the player on the screen.
     *
     *  Explanation from:
     *  https://roguebasin.com/index.php/Scrolling_map
     *
     *  A scrolling map is a term used in graphical 2D games, including roguelikes, for
     *  a map with a "camera" that follows the player. It is used for maps that are
     *  larger than that can be displayed on a single screen.

     *  Implementing scrolling maps is mathematically very simple. Let s be the
     *  dimensions of the screen, p be the player coordinates, and c be the coordinates
     *  of the upper left of the camera:

     *  camera := player - (screen / 2) 
     *
     *  All this means is that the camera location is the same as the
     *  player location, except offset by half the screen dimensions so that the player
     *  is nicely centered in the viewport.

     *  If the player is near the edge of the map, then the blank area outside the map
     *  might become visible. If you don't want this area to be displayed, and instead
     *  have the camera dock to the edge of the map, then the formula is revised to
     *  this, where m is the map size:

     *  If player < screen / 2, then camera := 0.  
     *  If player >= map - (screen / 2), then camera := map - screen.  
     *  Otherwise, camera := player - (screen / 2).  
     *
     *  Apply this procedure to each of the individual coordinates—first the x
     *  coordinates, and then the y ones.
     *
     */
    Vec2i camera;
    /* Visible area for the camera is NOT full screen, top and bottom of screen
     * are reserved for the GUI (which is more a HUD) and the message log. */
    int scrw = SCREEN_WIDTH;
    int scrh = SCREEN_HEIGHT - GUI_HEIGHT - MSG_HEIGHT;

    /* Get the camera */
    camera.x = g_player->pos.x - (scrw / 2);
    camera.y = g_player->pos.y - (scrh / 2);

    /* Adjust the camera if the player is too close to the edge */
    if(g_player->pos.x < (scrw / 2)) {
        camera.x = 0;
    } else if (g_player->pos.x >= MAP_WIDTH - (scrw / 2)) {
        camera.x = 1 + MAP_WIDTH - scrw;
    } else {
        camera.x = g_player->pos.x - (scrw / 2);
    }

    if(g_player->pos.y < (scrh / 2)) {
        camera.y = 0;
    } else if (g_player->pos.y >= MAP_HEIGHT - (scrh / 2)) {
        camera.y = 1 + MAP_HEIGHT - scrh;
    } else {
        camera.y = g_player->pos.y - (scrh / 2);
    }

    return camera;
}

void draw_msg_log(void) {
    /* This function draws the message log on the screen, with newer messages on
     * the top. It relies on the fact that the number of entries in the message
     * log list is less than screen height - 2. */
    int msgcount;
    int i,x;
    int contx = (SCREEN_WIDTH / 2) - (strlen("[Press any key to continue]")/2);
    Msg *cur = g_msgloghead;

    clear_screen(g_screenbuf);

    cull_msg(&g_msgloghead);
    msgcount = count_msg(&g_msgloghead);
    draw_hline(0,0,SCREEN_WIDTH,WHITE);
    x = (SCREEN_WIDTH / 2) - (strlen("Message Log")/2);
    draw_colorstr(x,0,"Message Log", BLACK, WHITE);
    i = 0;
    while (i < msgcount) {
        draw_str(0,i+1,cur->str);
        i++;
        cur = cur->next;
    }
    draw_str(contx, i+2, "[Press any key to continue]");
    
    draw_screen(g_screenbuf);
}

void draw_gameover(void) {
    if(!g_player) return;
    int lvl = (g_mapcur->lvl + 1) * 10;
    // Player name at 18,11 - 38-11
    // Level at 28,13
    int xoff = 28 - (strlen(g_player->name) / 2);
    char *depth = malloc(40 * sizeof(char));
    snprintf(depth,40, "%dft", lvl);
    draw_art(ART_TOMBSTONE);
    draw_str(xoff,11,g_player->name);
    draw_str(28,13,depth);
    // Final messages need to be drawn at 52,7 - 78,22
    free(depth);
}
