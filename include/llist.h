/*
* Toolbox
* Copyright (C) Zach Wilder 2022-2023
* 
* This file is a part of Toolbox
*
* Toolbox is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Toolbox is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Toolbox.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LLIST_H
#define LLIST_H

typedef void(*CleanupFunc)(void *);
typedef struct Node Node;
struct Node {
    void *data;
    Node *next;
    Node *prev;
};

typedef struct LList LList;
struct LList {
    Node *head;
    Node *tail;
    int datasize;
    CleanupFunc cleanupfunc;
};

Node* create_node(void *data, int size); 
void add_node_llist(LList *list, void *data);
Node* pop_llist(LList *list);
LList* create_llist(int datasize, CleanupFunc cleanup); 
void destroy_node(CleanupFunc cleanup, void *data);
void destroy_llist(LList *list);
int count_llist(LList *list);

#endif //LLIST_H
