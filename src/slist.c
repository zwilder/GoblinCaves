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

SList* create_SList(char *s) {
    SList *node = malloc(sizeof(SList));
    node->data = malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(node->data, s);
    node->length = strlen(s);
    node->next = NULL;
    return node;
}

SList* create_SList_blank(int strsize) {
    /* Create a node and allocate the memory for the string, but don't assign
     * anything to the string yet */
    SList *node = malloc(sizeof(SList));
    node->data = malloc(sizeof(char) * (strsize + 1));
    node->length = strsize;
    node->next = NULL;
    return node;
}

void push_SList_blank(SList **head, int strsize) {
    SList *newNode = create_SList_blank(strsize);
    SList *tmp;
    if(!(*head)) {
        *head = newNode;
        return;
    }
    if(!(*head)->next) {
        (*head)->next = newNode;
        return;
    }
    tmp = *head;
    while(tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

void destroy_SList(SList **head) {
    SList *tmp = *head;
    while(*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->data);
        free(tmp);
    }
}

void push_SList(SList **head, char *s) {
    SList *newNode = create_SList(s);
    SList *tmp;
    if(!(*head)) {
        *head = newNode;
        return;
    }
    if(!(*head)->next) {
        (*head)->next = newNode;
        return;
    }
    tmp = *head;
    while(tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

int count_SList(SList *node) {
    if(!node) {
        return 0;
    }
    return count_SList(node->next) + 1;
}

int count_chars_SList(SList *node, bool incSpace) {
    SList *tmp = node;
    int result = 0;
    while(tmp) {
        result += tmp->length;
        if(incSpace) {
            result += 1;
        }
        tmp = tmp->next;
    }
    return result;
}

SList* split_string(char *s, char delim) {
    SList *result = NULL;
    SList *tmp = NULL;
    int i = 0;
    int letters = 0;

    for(i = 0; s[i] != '\0'; i++) {
        /* move through string, looking at the letters */
        if((s[i] == delim) && (s[i+1] != delim)) {
            push_SList_blank(&result, letters);
            letters = 0;
        } else if (s[i+1] == '\0') {
            letters++;
            push_SList_blank(&result, letters);
        } else {
            letters++;
        }
    }
    tmp = result;
    letters = 0;
    for(i = 0; s[i] != '\0'; i++) {
        if(!tmp) {
            break;
        }
        if((s[i] == delim) && (s[i+1] != delim)) {
            tmp->data[letters] = '\0';
            tmp = tmp->next;
            letters = 0;
        }  else {
            tmp->data[letters] = s[i];
            letters++;
        }
    }
    tmp->data[letters] = '\0';
    return result;
}
