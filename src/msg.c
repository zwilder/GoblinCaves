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

Msg *g_msghead = NULL;
Msg *g_msgloghead = NULL;

Msg* create_msg(char *str){
    Msg *newmsg = malloc(sizeof(Msg));
    newmsg->str = malloc(strlen(str)+1);
    strcpy(newmsg->str,str);
    newmsg->next = NULL;
    return newmsg;
}

char* pop_msg(Msg **head){
    Msg *temp = (*head);
    char *str;
    (*head) = (*head)->next;
    str = malloc(strlen(temp->str)+1);
    strcpy(str, temp->str);
    free(temp->str);
    free(temp);
    return str;
}

void push_msg(Msg **head, char *str){
    if(!(*head)) {
        *head = create_msg(str);
    } else {
        Msg *newmsg = create_msg(str);
        newmsg->next = (*head);
        (*head) = newmsg;
    }
}

int count_msg(Msg **head) {
    int result = 0;
    Msg *tmp = *head;
    while(tmp) {
        result++;
        tmp = tmp->next;
    }
    return result;
}

void remove_last_msg(Msg **head) {
    if(!(*head)) {
        return;
    }
    if(!(*head)->next) {
        free((*head)->str);
        free(*head);
        return;
    }
    
    Msg *secondlast = *head;
    while(secondlast->next->next) {
        secondlast = secondlast->next;
    }

    free(secondlast->next->str);
    free(secondlast->next);

    secondlast->next = NULL;

    return;
}

void cull_msg(Msg **head) {
    int msgcount = count_msg(head);
    int screenrows = SCREEN_HEIGHT + GUI_HEIGHT + MSG_HEIGHT - 3;
    if(msgcount <= screenrows) {
        return;
    }
    while(msgcount > screenrows) {
        remove_last_msg(head);
        msgcount = count_msg(head);
    }
}

void destroy_msglist(Msg **head){
    if(!(*head)) {
        return;
    }

    while(*head) {
        free(pop_msg(head));
    }
}
