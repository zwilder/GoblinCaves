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

void start_log(void) {
    FILE *fp;
    fp = fopen("log.txt", "w+");
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    fprintf(fp, "Log start: %d-%02d-%02d %02d:%02d:%02d\n",
            now.tm_year + 1900, now.tm_mon + 1, now.tm_mday,
            now.tm_hour, now.tm_min, now.tm_sec);
    fclose(fp);
}

void write_log(char *msg) {
    FILE *fp;
    fp = fopen("log.txt", "a");
    /*
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    fprintf(fp, "%02d:%02d:%02d: ", now.tm_hour, now.tm_min, now.tm_sec);
    */
    log_time();
    fprintf(fp,"%s", msg);
    fprintf(fp, "\n");
    fclose(fp);
}

void log_tilemap(Tile *tilemap, int lvl) {
    FILE *fp;
    int x, y;
    if(NULL != tilemap) {
        fp = fopen("log.txt", "a");
        fprintf(fp, "\nMap %d:\n", lvl);
        for(y=0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                fprintf(fp,"%c", tilemap[get_map_index(x,y)].glyph.ch);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
    }
}

void log_time(void) {
    FILE *fp;
    fp = fopen("log.txt", "a");
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    fprintf(fp, "%02d:%02d:%02d: ", now.tm_hour, now.tm_min, now.tm_sec);
    fclose(fp);
}

void log_vec(Vec2i a) {
    FILE *fp;
    fp = fopen("log.txt", "a");
    fprintf(fp, "Vec2i(x%d,y%d)\n",a.x,a.y);
    fclose(fp);
}

void log_rect(Rect a) {
    FILE *fp;
    fp = fopen("log.txt", "a");
    fprintf(fp, "Rect(x%d,y%d,w%d,h%d)\n",
            a.pos.x, a.pos.y, a.dim.x, a.dim.y);
    fclose(fp);
}

void write_memorial(void) {
    /* This function completely ignores the "A function should do one specific
     * thing" ethos, but it works. Create a text file "memorial" of a character,
     * as an option when they die. It may be cool, eventually.*/
    if(!g_player) return;
    FILE *f;
    char fname[80];
    Glyph *screen = NULL;
    int w,h;
    int x,y,index;
    int lvl, xoff, i;
    char depth[10];
    char successmsg[180];
    Msg *msgit = NULL;
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    MList *monsterit = NULL;

    /* Make a filename and open it */
    snprintf(fname,80,"RIP_%s.txt",g_player->name);
    f = fopen(fname, "w+");
    if(!f) return;
    /* Write time to fnam */
    fprintf(f, "Memorial written: %d-%02d-%02d %02d:%02d:%02d\n**********\n",
            now.tm_year + 1900, now.tm_mon + 1, now.tm_mday,
            now.tm_hour, now.tm_min, now.tm_sec);

    /* Create a screen to draw the tombstone graphic on */
    screen = create_screen();
    w = SCREEN_WIDTH;
    h = SCREEN_HEIGHT;
    open_art(screen, ART_TOMBSTONE);
    xoff = strlen(g_player->name) / 2;
    i = 0;
    y = 11;
    for(x = 28 - xoff; x <= 28 + xoff; x++) {
        index = get_screen_index(x,y);
        if(g_player->name[i] == '\0') break;
        screen[index].ch = g_player->name[i];
        i++;
    }
    lvl = (g_mapcur->lvl + 1) * 10;
    snprintf(depth,10,"%dft",lvl);
    i = 0;
    y = 13;
    for(x = 28; x <= 28 + strlen(depth); x++) {
        if(depth[i] == '\0') break;
        index = get_screen_index(x,y);
        screen[index].ch = depth[i];
        i++;
    }

    /* Write the tombstone to the file */
    for(y = 0; y < h; y++) {
        for(x = 0; x < w; x++) {
            index = get_screen_index(x,y);
            if(screen[index].ch != '\0') {
                fputc(screen[index].ch,f);
            }
        }
        fputc('\n',f);
    }

    free(screen);
    /* Write the message log to the file*/
    fputs("\n**********\nFinal Messages\n**********\n",f);
    msgit = g_msgloghead;
    while(msgit) {
        fputs(msgit->str,f);
        fputs("\n",f);
        msgit = msgit->next;
    }

    /* Write the map to the file, with the player and goblins */
    screen = create_screen();
    fputs("\n**********\nLast Level\n**********\n",f);
    if(NULL != g_tilemap) {
        for(y=0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                index = get_screen_index(x,y);
                screen[index].ch = g_tilemap[get_map_index(x,y)].glyph.ch;
            }
        }
    }
    monsterit = g_mlist;
    lvl = g_mapcur->lvl;
    i = g_player->locID;
    while(monsterit) {
        if(monsterit->data) {
            if(monsterit->data->locID == i) {
                index = get_screen_index(monsterit->data->pos.x, monsterit->data->pos.y);
                screen[index].ch = monsterit->data->glyph.ch;
            }
        }
        monsterit = monsterit->next;
    }
    for(y = 0; y < h; y++) {
        for(x = 0; x < w; x++) {
            index = get_screen_index(x,y);
            if(screen[index].ch != '\0') {
                fputc(screen[index].ch,f);
            }
        }
        fputc('\n',f);
    }
    free(screen);

    /* Draw a message on the screen, "Memorial written to %s",fname */
    snprintf(successmsg,180,"Memorial written to %s", fname);
    write_log(successmsg);
    draw_msg_box(successmsg, WHITE, GREEN);
    draw_screen(g_screenbuf);
    get_input(); // ask for input to show the msgbox.
    /* Close the file */
    fclose(f);
}
