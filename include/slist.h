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
#ifndef SLIST_H
#define SLIST_H

struct SList {
    char *data;
    int length;
    struct SList *next;
};
typedef struct SList SList;

/*******************
 * slist.c functions
 *******************/
SList* create_SList(char *s);
SList* create_SList_blank(int strsize);
void push_SList_blank(SList **head, int strsize);
void destroy_SList(SList **head);
void push_SList(SList **head, char *s);
int count_SList(SList *node);
int count_chars_SList(SList *node, bool incSpace); 
SList* split_string(char *s, char delim); 

#endif
