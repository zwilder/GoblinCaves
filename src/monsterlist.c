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
    if(data) {
        newnode->data = data;
    } else {
        newnode->data = NULL;
        write_log("Attempting to create a MonsterList with NULL data!");
    }
    newnode->next = NULL;
    return newnode;
}

void push_mlist(MonsterList **head, Monster *data) {
    MonsterList *newnode;
    if(!(*head)) {
        *head = create_mlist(data);
    } else {
        newnode = create_mlist(data);
        newnode->next = (*head);
        (*head) = newnode;
    }
}

/*********
 * Utility
 *********/
int count_mlist(MonsterList *head) {
    int result = 0;
    if(!head) {
        return result;
    }
    /*
    if(!head->next) {
        result++;
        return result;
    }
    */
    MonsterList *tmp = head;
    while(tmp) {
        result++;
        tmp = tmp->next;
    }
    return result;
}

void move_mlist_player(MonsterList **fromlist, MonsterList **tolist) {
    remove_mlist_player(fromlist);
    push_mlist(tolist, g_player);
}

void remove_mlist_player(MonsterList **head) {
    /* Delete the node, not the player */
    MonsterList *tmp, *prev;
    tmp = *head;
    /* Head node has player */
    if(tmp && (tmp->data == g_player)){
        (*head)->next = tmp->next;
        write_log("Player found in list, node removed.");
        free(tmp);
        tmp = NULL;
        return;
    }

    /* Search for node with player */
    while(tmp && (tmp->data != g_player)) {
        prev = tmp;
        tmp = tmp->next;
    }

    /* If player not in list */
    if(!tmp) {
        write_log("Player not found in list!");
        return;
    }
    
    /* Unlink node */
    prev->next = tmp->next;
    write_log("Player found in list, node removed.");
    free(tmp);
    tmp = NULL;
}

    /*
Monster* pop_mlist_player(MonsterList *head) {
    Monster *result = NULL;
    MonsterList *cur, *prev;
    if(!head) {
        return result;
    }
    cur = head;
    while(cur) {
        if(check_flag(cur->data->flags,MF_PLAYER)){
            result = cur->data;
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    if(result){
        if(cur->next) {
            prev->next = cur->next;
        } else {
            prev->next = NULL;
        }
        if(cur) {
            free(cur);
            cur = NULL;
        }
    }
    return result;
}
    */

/*************
 * Destruction
 *************/
void destroy_mlist_at(MonsterList *head, MonsterList *key) {
    if(!head) {
        return;
    }
    if(!key) {
        return;
    }
    MonsterList *tmp = head;
    while(tmp) {
        if(tmp == key) {
            break;
        }
        tmp = tmp->next;
    }
    if(tmp) {
        free(tmp);
        tmp = NULL;
    }
}

void remove_mlist_by_flag(MonsterList *head, MonsterFlags flag) {
    if(!head) {
        return;
    }
    MonsterList *tmp = head;
    MonsterList *cur;
    while(tmp) {
        cur = tmp;
        if(check_flag(cur->data->flags, flag)) {
            free(cur);
            cur = NULL;
        }
        tmp = tmp->next;
    }
}

void cull_mlist(MonsterList **head) {
    /* Delete the monster, delete the node*/
    MonsterList *tmp, *prev, *cur;
    tmp = *head;
    /* Head node has MF_NONE*/
    if(tmp && (check_flag(tmp->data->flags,MF_NONE))){
        (*head)->next = tmp->next;
        write_log("MF_NONE found in head, node removed.");
        if(tmp->data){
            free(tmp->data);
            tmp->data = NULL;
        }
        free(tmp);
        tmp = NULL;
    }

    /* Search for node with MF_NONE*/
    while(tmp) {
        cur = tmp;
        if(cur->data) {
            if(check_flag(cur->data->flags, MF_NONE)) {
                free(cur->data);
                write_log("MF_NONE found in list, node removed.");
                cur->data = NULL;
                free(cur);
                cur = NULL;
            }
            prev->next = tmp->next;
            tmp = tmp->next;
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }

    /*
    if(!head) {
        return;
    }
    MonsterList *tmp = head;
    MonsterList *cur;
    while(tmp) {
        cur = tmp;
        if(!check_flag(cur->data->flags, MF_ALIVE)) {
            if(cur->data) {
                free(cur->data);
            }
            free(cur);
            cur = NULL;
        }
        tmp = tmp->next;
    }
    */
}

void destroy_mlist(MonsterList **head) {
    if(!(*head)) {
        return;
    }

    MonsterList *tmp;
    while(*head) {
        tmp = *head;
        *head = (*head)->next; 
        if(tmp->data) {
            destroy_monster(tmp->data);
            tmp->data = NULL;
        }
        if(tmp){
            free(tmp);
        }
    }
    *head = NULL;
}
