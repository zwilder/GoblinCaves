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

/*******
 * SList
 *
 * A simple linked list of nodes containing a string (char*) and an int with the
 * length of the string. Portable outside of this project. 
 *******/

SList* create_SList(char *s) {
    /* Create a SList node, calculate the length of string s (don't forget the
     * \0 at the end!), store both the string and the length, and return the
     * node.
     */
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
    /* Push a blank node onto the SList, reserving space for a string of strsize
     * length in the node */
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
    /* Destroy a SList, looping through and freeing the memory for the stored
     * strings before freeing the memory used by the node. */
    SList *tmp = *head;
    while(*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->data);
        free(tmp);
    }
}

void push_SList(SList **head, char *s) {
    /* Push a new node onto the SList, containing string s */
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
    /* Count and return the number of nodes in the SList */
    if(!node) {
        return 0;
    }
    return count_SList(node->next) + 1;
}

int count_chars_SList(SList *node, bool incSpace) {
    /* Count and return the number of characters in each string in SList,
     * optionally including the spaces */
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

char* get_string_SList(SList *node) {
    /* Combine all the strings in SList into one string, and then return it */
    if(!node) {
        return NULL;
    }
    char *result = malloc((sizeof(char) * count_chars_SList(node, true)) + 1);
    SList *tmp = node;
    int i = 0;
    int letters = 0;
    while(tmp) {
        for(i = 0; tmp->data[i] != '\0'; i++) {
            result[letters] = tmp->data[i];
            letters++;
        }
        if(tmp->data[i+1] != '\0') {
            result[letters] = ' ';
        }
        letters++;
        tmp = tmp->next;
    }
    for(i = 0; i < count_chars_SList(node,true); i++) {
        if(result[i] == '\0') {
            result[i] = ' ';
        }
    }
    result[i] = '\0';
    return result;
}

void add_SList(SList **to, SList **from) {
    /* Add all words from "from" to back of "to" list */
    if(!(*to) || !(*from)) {
        return;
    }
    SList *tmp = *to;
    while(tmp->next) {
        tmp = tmp->next;
    }

    while(*from) {
        tmp->next = *from;
        tmp = tmp->next;
        *from = (*from)->next;
    }
}

SList* split_string(char *s, char delim) {
    /* Nifty function that takes a string s, splits it by delimeter delim,
     * and returns the results as an Slist*
     */
    if(!s) {
        return NULL;
    }
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
