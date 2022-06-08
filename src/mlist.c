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

MList* create_mlist(Monster *data) {
    if(!data) {
        return NULL;
    }
    MList *newnode = malloc(sizeof(MList));

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void push_mlist(MList **head, Monster *data) {
    if(!data) {
        return;
    }
    if(!(*head)) {
        *head = create_mlist(data);
        return;
    }
    MList *newnode = create_mlist(data);
    (*head)->prev = newnode;
    newnode->next = *head;
    *head = newnode;
}

void transfer_mlist(MList **from, MList **to, Monster *data) {
    if(!(*from)) {
        return;
    }
    MList *tmp = NULL;
    MList *cur = *from;
    /* Find monster in from list */
    while(cur) {
        if(cur->data == data) {
            break;
        }
        cur = cur->next;
    }
    if(!cur) {
        /* Didnt find monster in list */
        return;
    }
    /* Unlink node */
    tmp = cur; 
    if(cur->next) {
        cur->next->prev = cur->prev;
    }
    if(tmp->prev) {
        tmp->prev->next = tmp->next;
    } else {
        /* tmp is head node of from list, head node needs to move */
        *from = tmp->next;
    }

    /* Put in to list */
    if(!(*to)) {
        *to = cur;
        (*to)->next = NULL;
        (*to)->prev = NULL;
        return;
    }
    (*to)->prev = cur;
    cur->next = *to;
    *to = cur;
}

Monster* find_mlist(MList *head, int flags) {
    if(!head) {
        return NULL;
    }
    MList *result = head;
    while(result) {
        if(check_flag(result->data->flags, flags)) {
            break;
        }
        result = result->next;
    }
    return result->data;
}

void sort_mlist(MList **head) {
    /* Sort mlist by available action points, so monsters with the most action
     * points will take their turn first */
}

int count_mlist(MList *head) {
    if(head) {
        return (count_mlist(head->next) + 1);
    } else {
        return 0;
    }
}

void destroy_mlist(MList **head) {
    if(!(*head)) {
        return;
    }
    MList *tmp = *head;
    while(*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}
