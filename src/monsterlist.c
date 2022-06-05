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

/**********
 * Creation
 **********/
MonsterList* create_mlist(Monster *data) {
    MonsterList *newnode = malloc(sizeof(MonsterList));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

MonsterList* add_mlist_empty(MonsterList *head, Monster *data) {
    if(head) {
        return head; /*Function only for empty*/
    }
    MonsterList *tmp = create_mlist(data);
    head = tmp;
    head->next = head;

    return head;
}

MonsterList* add_mlist_front(MonsterList *head, Monster *data) {
    if(!head) {
        return add_mlist_empty(head, data);
    }

    MonsterList *tmp = create_mlist(data);
    tmp->next = head->next;
    head->next = tmp;

    return head;
}

MonsterList* add_mlist_back(MonsterList *head, Monster *data) {
    if(!head) {
        return add_mlist_empty(head, data);
    }
    MonsterList *tmp = create_mlist(data);
    tmp->next = head->next;
    head->next = tmp;
    head = tmp;

    return head;
}

/*********
 * Utility
 *********/
int count_mlist(MonsterList *head) {
    MonsterList *tmp = head;
    int result = 0;
    if(head) {
        do {
            tmp = tmp->next;
            result++;
        } while (tmp != head);
    }
    return result;
}

Monster* pop_mlist_at(MonsterList *head, MonsterList *key) {
    if(!head) {
        return NULL;
    }
    MonsterList *cur = head;
    MonsterList *prev;
    Monster *result;

    /* Find the node */
    while(cur != key) {
        if(cur->next == head) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    /* Check if node is only node */
    if(cur->next == head) {
        head = NULL;
        result = cur->data;
        free(cur);
        return result;
    }

    /* If more than one node: */
    if(cur == head) {
        /*is it the first node?*/
        prev = head;
        while(prev->next != head) {
            prev = prev->next;
        }
        head = cur->next;
        prev->next = head;
    } else if ((cur->next == head) && (cur == head)) {
        /*is it the head node?*/
        prev->next = head;
    } else {
        /*is it somewhere in between?*/
        prev->next = cur->next;
    }
    result = cur->data;
    free(cur);
    return result;
}

Monster* pop_mlist_player(MonsterList *head) {
    MonsterList *tmp = head;
    Monster *player = NULL;
    if(head) {
        do {
            if(check_flag(tmp->data->flags, MF_PLAYER)) {
                player = pop_mlist_at(head, tmp);
            }
            tmp = tmp->next;
        } while (tmp != head);
    }
    return player;
}

MonsterList* pop_mlist_front(MonsterList **head) {
    MonsterList *p = *head;
    *head = (*head)->next;
    return(p);
}
/*************
 * Destruction
 *************/
void destroy_mlist_at(MonsterList *head, MonsterList *key) {
    if(!head) {
        return;
    }
    MonsterList *cur = head;
    MonsterList *prev;

    /* Find the node */
    while(cur != key) {
        if(cur->next == head) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    /* Check if node is only node */
    if(cur->next == head) {
        head = NULL;
        free(cur);
        return;
    }

    /* If more than one node: */
    if(cur == head) {
        /*is it the first node?*/
        prev = head;
        while(prev->next != head) {
            prev = prev->next;
        }
        head = cur->next;
        prev->next = head;
    } else if ((cur->next == head) && (cur == head)) {
        /*is it the head node?*/
        prev->next = head;
    } else {
        /*is it somewhere in between?*/
        prev->next = cur->next;
    }
    free(cur);
}

    
void destroy_mlist(MonsterList **head) {
    if(!(*head)) {
        return;
    }
    MonsterList *tmp;
    MonsterList *p = (*head)->next;
    (*head)->next = NULL;
    while(p) {
        tmp = p;
        p = p->next;
        free(tmp->data);
        free(tmp);
    }
    (*head) = NULL;
}

void cull_mlist(MonsterList *head) {
    /* Removes dead monsters */
    MonsterList *tmp = head;
    MonsterList *cur;
    if(head) {
        do {
            cur = tmp;
            tmp = tmp->next;
            if(!check_flag(cur->data->flags, MF_ALIVE)) {
                /* Monster dead, remove it from list */
                destroy_mlist_at(head, cur);
            }
        } while (tmp != head);
    }
}
