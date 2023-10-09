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

/*****
 * MList (Monster List)
 *
 * A double linked list, with each node containing a Monster. The game has one
 * big fat list, and each monster keeps track of the level it's on. Having a
 * list for each level got messy and was really unecessary - it makes much more
 * sense to just let the Monster keep track of the level it's on.
 *
 *****/
MList *g_mlist = NULL;

MList* create_mlist(Monster *data) {
    /* Creates a MList node, containing Monster data */
    if(!data) {
        return NULL;
    }
    MList *newnode = calloc(1, sizeof(MList));

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void push_mlist(MList **head, Monster *data) {
    /* Pushes a Monster (data) onto the MList, keeping track of the previous
     * node */
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

void destroy_mlist_node(MList **head, MList *del) {
    /* Removes a node from MList by first fixing the next and previous nodes to
     * point to each other instead of this node, then freeing the memory. */
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

    if(del->data) {
        destroy_monster(del->data);
        del->data = NULL;
    }
    free(del);
}

void destroy_mlist_monster(MList **head, Monster *target) {
    /* Finds a Monster (target) in the MList, and destroys the node containing
     * it. */
    MList *del = *head;
    while(del) {
        if(del->data == target) {
            break;
        }
        del = del->next;
    }
    if(del) {
        destroy_mlist_node(head, del);
    }
}

Monster* find_mlist(MList *head, int flags) {
    /* Returns a pointer to the FIRST Monster in the MList that matches the
     * flags passed in. */
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

Monster* monster_at_pos(MList *head, Vec2i pos, int locID) {
    /* Returns a pointer to a Monster that exists at a position (pos) in a
     * specific location (locID) */
    MList *cur = head;
    while(cur) {
        if(cur->data->locID == locID) {
           if(eq_vec(cur->data->pos, pos)) {
                  break;
           }
        }
        cur = cur->next;
    }
    if(!cur) {
        return NULL;
    }
    return cur->data;
}

int count_mlist(MList *head) {
    /* Counts and returns the total number of nodes in an MList */
    if(head) {
        return (count_mlist(head->next) + 1);
    } else {
        return 0;
    }
}

void destroy_mlist(MList **head) {
    /* Destroys an MList, looping through each node and destroying it, freeing
     * the memory as it goes. */
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

/*****
 * Broken/Depreciated/Work in Progress functions below. Eventually these might
 * be fixed or useful.
 *****/
void sort_mlist(MList **head) {
    /* Sort mlist by available action points, so monsters with the most action
     * points will take their turn first. Function not in mlist.h.*/
}

void transfer_mlist(MList **from, MList **to, Monster *data) {
    /* This function does not work and should absolutely not be used. I
     * originally had multiple MList (one for each level) and this was to
     * transfer a Monster from one level to the next. For some reason, this
     * caused all sorts of heck to break loose and things to break. I never did
     * figure out what was going wrong, so instead of deleting this and
     * pretending it never happened, I left it here in all of it's messy glory
     * to figure out later.
     * 
     * The function isn't listed in mlist.h, so if I ever fix this I'll need to
     * remember to slap it back in there. 
     * */
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
