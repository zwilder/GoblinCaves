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

void log_map(void) {
    FILE *fp;
    int x, y;
    if(NULL != g_map) {
        fp = fopen("log.txt", "a");
        fprintf(fp, "\nMap:\n");
        for(y=0; y < MAP_HEIGHT; y++){
            for(x = 0; x < MAP_WIDTH; x++){
                fprintf(fp,"%c", g_map[get_map_index(x,y)].glyph.ch);
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

void log_leaves(Node *node) {
    FILE *fp;
    if(NULL == node) {
        return;
    }
    if(NULL == node->leftChild) {
        fp = fopen("log.txt", "a");
        fprintf(fp, "Leaf with data: ");
        fprintf(fp, "\n\t-");
        log_rect(node->data);
        fclose(fp);
    }
    log_leaves(node->leftChild);
    log_leaves(node->rightChild);
}
