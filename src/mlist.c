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

/*
 * Latest idea: Have multiple MLists isn't cutting it. What if... I have one big
 * MList? each monster can keep track of it's own identifier, and the identifier
 * could be kept track of in the node. The identifier would be generated when
 * the node is created (create_mlist) by using a simple:
 *      static int idcounter = 0;
 *      (MList creation/initialization stuff)
 *      newnode->id = idcounter;
 *      idcounter++;
 * Monsters should also keep track of the level they are currently on.
 */
MList *g_mlist = NULL;

MList* create_mlist(Monster *data) {
    if(!data) {
        return NULL;
    }
    MList *newnode = calloc(1, sizeof(MList));
    //write_log("Creating MList node!");
    //write_log(data->name);

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void push_mlist(MList **head, Monster *data) {
    if(!data) {
        write_log("Failed push_mlist()!");
        return;
    }
    if(!(*head)) {
        *head = create_mlist(data);
        write_log("Head empty, created MList.");
        return;
    }
    MList *newnode = create_mlist(data);
    (*head)->prev = newnode;
    newnode->next = *head;
    *head = newnode;
}

void transfer_mlist(MList **from, MList **to, Monster *data) {
    /* Function does not work */
    if(!(*from)) {
        return;
    }
    if(!data) {
        write_log("Attempted transfer of NULL monster!");
        return;
    }
    char msg[80] = "Transferring: ";
    strcat(msg, data->name);
    write_log(msg);
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
    write_log("Found in from list!");
    /* Unlink node */
    destroy_mlist_node(from, cur);
    write_log("Node unlinked.");

    /* Put in to list */
    if(!(*to)) {
        write_log("To list empty, pushing node to To list.");
        write_log(data->name);
        push_mlist(to, data);
        return;
    } 
    push_mlist(to, data);
    /*
    (*to)->prev = cur;
    cur->next = *to;
    *to = cur;
    */
}

void destroy_mlist_node(MList **head, MList *del) {
    if(!(*head) || !del) {
        return;
    }
    if((*head) == del) {
        *head = del->next;
    }
    if(del->next) {
        del->next->prev = del->prev;
    }
    if(del->prev) {
        del->prev->next = del->next;
    }

    //write_log("Destroy mlist node!");
    free(del);
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
        if(tmp->data) {
            destroy_monster(tmp->data);
        }
        free(tmp);
    }
}
