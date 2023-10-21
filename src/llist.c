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

#include <toolbox.h>

/*****
 * Generic Linked List, LList.
 *
 * This linked list will (eventually) replace the simple linked lists in the
 * other toolbox files - it should be more robust and simple to use. The only
 * potential hazard is trying to mix and match data types in a single list, or
 * if a cleanup function isn't defined for the data - could cause weirdness.
 *****/
Node* create_node(void *data, int size) {
    /* Creates a new node that contains a pointer to any data type. Allocates
     * memory for the node, and if the data is NULL it allocates memory of
     * specified size to hold that data */
    Node *newnode = malloc(sizeof(Node));
    if(!data) {
        newnode->data = malloc(size);
    }
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void add_node_llist(LList *list, void *data) {
    /* Adds a new node to a llist that contains a pointer to data. Takes care of
     * updating the head/tail references for the list  */
    if(!list || !data) return;
    Node *newnode = create_node(data, list->datasize);
    if(!list->head) {
        // No head means this node is the first, and also the tail
        list->tail = newnode;
    }
    newnode->next = list->head;
    list->head = newnode;
}

Node* pop_llist(LList *list) {
    /* Removes the head of a llist, and returns a pointer to it */
    if(!list) return NULL;
    Node *result = list->head;
    if(result) {
        list->head = list->head->next;
    }
    if(!list->head) list->tail = NULL; // No head, no tail
    return result;
} 

LList* create_llist(int datasize, CleanupFunc cleanup) {
    /* Creates a llist to hold a specific type of data, of size datasize, and if
     * the data has a cleanup function - keep track of it. */
    LList *list = malloc(sizeof(LList));
    list->head = NULL;
    list->tail = NULL;
    list->cleanupfunc = cleanup;
    list->datasize = datasize;
    return list;
}

void destroy_node(CleanupFunc cleanup, void *data) {
    /* Calls the cleanup function specified by the list on the data */
    if(!data) return;
    if(cleanup) {
        cleanup(data);
    } else {
        free(data);
    }
}

void destroy_llist(LList *list) {
    /* Pops the head node off a list, checks to see if it has data, calls the
     * cleanup function on the data, frees the node, and repeats until the list
     * is empty. Then, it frees the list. */
    if(!list) return;
    Node *tmp = pop_llist(list);
    while(tmp) {
        if(tmp->data) {
            destroy_node(list->cleanupfunc, tmp->data);
        }
        free(tmp);
        tmp = pop_llist(list);
    }
    free(list);
}

int count_llist(LList *list) {
    /* Return the total number of nodes in a llist */
    Node *tmp = list->head;
    int result = 0;
    while(tmp) {
        result++;
        tmp = tmp->next;
    }
    return result;
}

