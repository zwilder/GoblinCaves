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
#ifndef MSG_H
#define MSG_H

struct Msg {
    char *str;
    struct Msg *next;
};

typedef struct Msg Msg;

Msg* create_msg(char *str);
char* pop_msg(Msg **head);
void push_msg(Msg **head, char *str);
int count_msg(Msg **head); 
void destroy_msglist(Msg **head);

#endif
