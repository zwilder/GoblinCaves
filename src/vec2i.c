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
const Vec2i NULLVEC = {INT_MIN, INT_MIN};

/*******
 * Vec2i is a two dimensional integer vector container - an x,y coordinate pair.
 * It has many (many) uses outside of just graphing, however, and I tend to
 * write a version of it for almost every project. The name was borrowed from
 * SFML (Simple Fast Media Layer). I liked the name they used more than what I
 * used to call it ("Point" - yeah, that sucks), so I stole it. I could use the
 * functions contained here as a template for similar containers (two
 * dimensional floats, short ints, chars (uint8_t), etc).
 *
 * This file contains all the functions that make Vec2i useful - it is portable
 * and requires only vec2i.h. (Note: the include <goblincaves.h> above is just
 * to stay consistent with in this project; everything uses a common header
 * file.
 *
 ********/

/********
 * Vec2i
 ********/
Vec2i make_vec(int x, int y) {
    /* Takes an x,y pair of ints and returns a Vec2i */
    Vec2i result = {};
    result.x = x;
    result.y = y;
    return result;
}
Vec2i add_vec(Vec2i a, Vec2i b) {
    /* Takes two Vec2i, adds them together, and returns the result */
    Vec2i result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vec2i subtract_vec(Vec2i a, Vec2i b) {
    /* Takes two Vec2i, subtracts them, and returns the result */
    Vec2i result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

bool eq_vec(Vec2i a, Vec2i b) {
    /* Takes two Vec2i and returns true if they equal each other */
    return ((a.x == b.x) && (a.y == b.y));
}

bool vec_null(Vec2i a) {
    /* Checks a Vec2i to see if it is NULLVEC */
    return (eq_vec(NULLVEC, a));
}

int man_dist(Vec2i a, Vec2i b) {
    /* Returns the manhattan distance between two Vec2i */
    return (abs(a.x - b.x) + abs(a.y - b.y));
}

/***********
 * Vec2iList
 *
 * Simple linked list of Vec2i
 ***********/

Vec2iList* create_Vec2i_list(Vec2i pos) {
    /* Allocates memory for a Vec2iList node, and returns a pointer to it. */
    Vec2iList *newnode = malloc(sizeof(Vec2iList));
    newnode->item = pos;
    newnode->next = NULL;
    return newnode;
}

void push_Vec2i_list(Vec2iList **head, Vec2i pos) {
    /* Takes a pointer to a head node of a Vec2i list, and:
     * 1) Checks if head is NULL, if it is it creates a node and returns.
     * 2) Creates a new node with data "pos"
     * 3) Assigns the new node's next value to head.
     */
    if(!(*head)) {
        *head = create_Vec2i_list(pos);
        return;
    }
    Vec2iList *newnode = create_Vec2i_list(pos);
    newnode->next = *head;
    *head = newnode;
}

Vec2i pop_Vec2i_list(Vec2iList **head) {
    /* Takes a pointer to a head node of a Vec2i list, and:
     * 1) Returns NULLVEC if head is NULL
     * 2) Takes the data from the head node
     * 3) Sets the pointer for the head node to the next item
     * 4) Frees the old head node
     * 5) Returns the data from the old head node
     */
    if(!(*head)) {
        return (NULLVEC);
    }
    Vec2iList *tmp = *head;
    *head = (*head)->next;
    Vec2i result = tmp->item;
    free(tmp);
    return result;
}

int count_Vec2i_list(Vec2iList *head) {
    /* Counts the items in a Vec2i list, returns the count */
    if(!head) {
        return 0;
    }
    return (count_Vec2i_list(head->next) + 1);
}

void destroy_Vec2i_list(Vec2iList **head) {
    /* Frees the memory for a Vec2i list */
    if(!(*head)) {
        return;
    }
    Vec2iList *tmp = NULL;
    while(*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

bool Vec2i_list_contains(Vec2iList *head, Vec2i pos) {
    /* Checks to see if the Vec2iList contains a Vec2i pos */
    bool result = false;
    Vec2iList *tmp = head;
    while(tmp) {
        if(eq_vec(tmp->item, pos)) {
            result = true;
            break;
        }
        tmp = tmp->next;
    }
    return result;
}

/*********
 * Vec2iPQ
 *
 * Priority queue Vec2i list, each node contains a Vec2i item and a priority p.
 * New items are added to the list in increasing priority so the items with
 * highest priority are at the top of the list. 
 *********/
Vec2iPQ* create_Vec2iPQ(Vec2i item, int p) {
    /* Creates a Vec2iPQ node, with Vec2i item and priority int p */
    Vec2iPQ *newnode = malloc(sizeof(Vec2iPQ));
    newnode->item = item;
    newnode->p = p;
    newnode->next = NULL;
    return newnode;
}

Vec2i peek_Vec2iPQ(Vec2iPQ **head) {
    /* Returns the value of the Vec2iPQ node at the top of the list */
    return((*head)->item);
}

Vec2i pop_Vec2iPQ(Vec2iPQ **head) {
    /* Takes the top item off the Vec2iPQ list, sets the next node as the new
     * head, stores the Vec2i list, frees the memory of the old top node, and
     * returns the stored list. */
    if(!(*head)) {
        return NULLVEC;
    }
    Vec2iPQ *tmp = *head;
    Vec2i result = tmp->item;
    *head = (*head)->next;
    free(tmp);
    return result;
}

void push_Vec2iPQ(Vec2iPQ **head, Vec2i item, int p) {
    /* Adds a new Vec2i item with priority p to a Vec2iPQ list. */
    if(!(*head)) {
        *head = create_Vec2iPQ(item, p);
        return;
    }
    Vec2iPQ *start = *head;
    Vec2iPQ *newnode = create_Vec2iPQ(item, p);

    if((*head)->p > p) {
        newnode->next = *head;
        *head = newnode;
    } else {
        while(start->next && (start->next->p < p)) {
            start = start->next;
        }
        newnode->next = start->next;
        start->next = newnode;
    }
}

void destroy_Vec2iPQ(Vec2iPQ **head) {
    /* Frees all the nodes in a Vec2iPQ list */
    if(!(*head)) {
        return;
    }
    Vec2iPQ *tmp = NULL;
    while(*head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

/*********
 * Vec2iHT
 *
 * Hash table Vec2i list. This list creates a hash table containing nodes with a
 * Vec2i value/key pair.  
 *********/
unsigned long Vec2i_hash(Vec2i key, int size) {
    /* Simple hash function - nothing fancy here */
    return(((key.y << 16) ^ key.x) % size);
}

Vec2iHTItem* create_Vec2iHTItem(Vec2i key, Vec2i value) {
    /* Given a Vec2i key/value pair, return a Vec2iHTItem node */
    Vec2iHTItem *item = malloc(sizeof(Vec2iHTItem));
    item->key = key;
    item->value = value;
    return item;
}

Vec2iHT* create_Vec2iHT(int size) {
    /* Create a Vec2iHT table of int size, allocating memory, set each item to
     * NULL, and returning the table */
    int i = 0;
    Vec2iHT *table = malloc(sizeof(Vec2iHT));
    table->size = size;
    table->count = 0;
    table->items = calloc(table->size, sizeof(Vec2iHTItem));
    for(i = 0; i < table->size; i++) {
        table->items[i] = NULL;
    }
    table->ofbuckets = create_Vec2iHT_ofbuckets(table);
    return table;
}

void destroy_Vec2iHTItem(Vec2iHTItem *item) {
    /* This frees the memory held by a Vec2iHTItem...
     * Why this is it's own function is a total mystery that can never be
     * solved. Just kidding, the prototype function I based this off of stored a
     * key/value pair of strings (char*), so for the item to be destroyed in
     * that case the memory needed to be released for both key and value
     * strings, then the item.*/
    if(!item) {
        return;
    }
    free(item);
}

void destroy_Vec2iHT(Vec2iHT *table) {
    /* This loops through a Vec2iHT table, free the memory held by each item
     * before freeing the memory held by the table */
    int i = 0;
    Vec2iHTItem *item = NULL;
    for(i = 0; i < table->size; i++) {
        item = table->items[i];
        destroy_Vec2iHTItem(item);
    }
    destroy_Vec2iHT_ofbuckets(table);
    free(table->items);
    free(table);
}

void handle_Vec2iHT_collision(Vec2iHT *table, 
        unsigned long index, Vec2iHTItem *item) {
    /* If an item inserted into a Vec2iHT ends up with the same hash, this
     * function puts the item into a "Bucket" associated with the hash */
    Vec2iHTList *head = table->ofbuckets[index];
    if(!head) {
        /* Create the list */
        head = create_Vec2iHTList(item);
        table->ofbuckets[index] = head;
    } else {
        table->ofbuckets[index] = insert_Vec2iHTList(head, item);
    }
}

void insert_Vec2iHT(Vec2iHT *table, Vec2i key, Vec2i value) {
    /* This function takes a key/value pair of Vec2i, generates a hash for the
     * pair. Then it checks to see if an item at that hash index exists. If
     * there isn't an item there, it stores the new key/value pair there. If
     * there is an item there, and it has the same key as the item we just
     * passed in, we update the value of the item. If there's an item there with
     * a different key, then we handle the collision and put the item into an
     * overflow "bucket".
     */
    Vec2iHTItem *item = create_Vec2iHTItem(key,value);
    int index = Vec2i_hash(key,table->size);
    Vec2iHTItem *cur = table->items[index];

    if(!cur) {
        /* Key does not exist */
        if(table->count == table->size) {
            /* Hash table full */
            destroy_Vec2iHTItem(item);
            return;
        }
        table->items[index] = item;
        table->count += 1;
    } else {
        /* Key exists */
        if(eq_vec(cur->key, key)) {
            /* Same key, update value, destroy unneeded new item*/
            table->items[index]->value = value;
            destroy_Vec2iHTItem(item); 
        } else {
            handle_Vec2iHT_collision(table, index, item);
        }
    }
}

Vec2i search_Vec2iHT(Vec2iHT *table, Vec2i key) {
    /* This is the money function - it searches a given Vec2iHT table for a key,
     * returning the value. */
    if(vec_null(key) || !table) {
        return NULLVEC;
    }
    int index = Vec2i_hash(key, table->size);
    Vec2iHTItem *item = table->items[index];
    Vec2iHTList *head = table->ofbuckets[index];
    while(item) {
        if(eq_vec(item->key, key)) {
            return item->value;
        }
        if(!head) {
            return NULLVEC;
        }
        item = head->item;
        head = head->next;
    }
    return NULLVEC;
}

Vec2iHTList** create_Vec2iHT_ofbuckets(Vec2iHT *table) {
    /* This function creates the list of overflow buckets for a given Vec2iHT
     * table */
    Vec2iHTList **buckets = calloc(table->size, sizeof(Vec2iHTList*));
    int i;
    for(i = 0; i < table->size; i++) {
        buckets[i] = NULL;
    }
    return buckets;
}

void destroy_Vec2iHT_ofbuckets(Vec2iHT *table) {
    /* This function destroys the list of overflow buckets in a table, freeing
     * the memory as it goes */
    Vec2iHTList **buckets = table->ofbuckets;
    int i;
    for(i = 0; i < table->size; i++) {
        destroy_Vec2iHTList(buckets[i]);
    }
    free(buckets);
}

void delete_Vec2iHT(Vec2iHT *table, Vec2i key) {
    /* This chonky function finds a key/value pair by the key, removing it from
     * the hash table. Along the way, it checks the overflow buckets and moves
     * them "up the chain" if they exist. */
    int index = Vec2i_hash(key, table->size);
    Vec2iHTItem *item = table->items[index];
    Vec2iHTList *head = table->ofbuckets[index];
    Vec2iHTList *node = NULL;
    Vec2iHTList *cur = NULL;
    Vec2iHTList *prev = NULL;

    if(!item) {
        /*Item doesn't exist */
        return;
    }
    if(!head && eq_vec(item->key, key)) {
        /* No collision chain, remove item set table index to NULL */
        table->items[index] = NULL;
        destroy_Vec2iHTItem(item);
        table->count--;
        return;
    } else if (head) {
        /* Collision chain exists */
        if(eq_vec(item->key, key)) {
            /* Remove this item and set head of list as the new item */
            destroy_Vec2iHTItem(item);
            node = head;
            head = head->next;
            node->next = NULL;
            table->items[index] = create_Vec2iHTItem(node->item->key, 
                    node->item->value);
            destroy_Vec2iHTList(node);
            table->ofbuckets[index] = head;
            return;
        }
        cur = head;
        prev = NULL;
        while(cur) {
            if(eq_vec(cur->item->key, key)) {
                if(!prev) {
                    /* First element of chain, remove chain */
                    destroy_Vec2iHTList(head);
                    table->ofbuckets[index] = NULL;
                    return;
                } else {
                    /* Somewhere else in chain */
                    prev->next = cur->next;
                    cur->next = NULL;
                    destroy_Vec2iHTList(cur);
                    table->ofbuckets[index] = head;
                    return;
                }
            }
            cur = cur->next;
            prev = cur;
        }
    }
}

/*************
 * Vec2iHTList
 *
 * Simple linked list of Vec2iHTItems - really shouldn't be used directly,
 * mostly a helper for the Vec2iHT.
 *************/
Vec2iHTList* create_Vec2iHTList(Vec2iHTItem *item) {
    /* Creates a node for the Vec2iHTList, containing a Vec2iHTItem */
    Vec2iHTList *list = malloc(sizeof(Vec2iHTList));
    if(!list) {
        return NULL;
    }
    list->item = item;
    list->next = NULL;
    return list;
}

Vec2iHTList* insert_Vec2iHTList(Vec2iHTList *headref, Vec2iHTItem *item) {
    /* Inserts a new Vec2iHTItem into the list */
    Vec2iHTList *newnode = create_Vec2iHTList(item);
    Vec2iHTList *tmp = NULL;
    if(!headref) {
        headref = newnode;
        return headref;
    }else if (!headref->next) {
        headref->next = newnode;
        return headref;
    }
    tmp = headref;
    while(tmp->next->next) {
        /* Gets last node */
        tmp = tmp->next;
    }
    tmp->next = newnode;
    return headref;
}

Vec2iHTItem* pop_Vec2iHTList(Vec2iHTList **headref) {
    /* Takes the top item of the Vec2iHTList out of the list, returning the
     * Vec2iHTItem associated with it. */
    if(!(*headref)) {
        return NULL;
    }
    if(!(*headref)->next) {
        return NULL;
    }
    Vec2iHTList *node = (*headref)->next;
    Vec2iHTList *tmp = *headref;
    Vec2iHTItem *item = NULL;
    tmp->next = NULL;
    *headref = node;
    free(tmp->item);
    free(tmp);
    return item;
}

void destroy_Vec2iHTList(Vec2iHTList *headref) {
    /* Destroys a Vec2iHTList, looping through each item and freeing memory as
     * it goes */
    Vec2iHTList *tmp = headref;
    while(headref) {
        tmp = headref;
        headref = headref->next;
        free(tmp->item);
        free(tmp);
    }
}
