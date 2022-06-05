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
#ifndef MONSTERLIST_H
#define MONSTERLIST_H

struct MonsterList {
    Monster *data;
    struct MonsterList *next;
};

typedef struct MonsterList MonsterList;

/**********
 * Creation 
 **********/
MonsterList* create_mlist(Monster *data);
MonsterList* add_mlist_empty(MonsterList *head, Monster *data);
MonsterList* add_mlist_front(MonsterList *head, Monster *data);
MonsterList* add_mlist_back(MonsterList *head, Monster *data);

/*********
 * Utility
 *********/
int count_mlist(MonsterList *head);
MonsterList* pop_mlist_front(MonsterList **head);
Monster* pop_mlist_at(MonsterList *head, MonsterList *key);
Monster* pop_mlist_player(MonsterList *head);

/*************
 * Destruction
 *************/
void destroy_mlist_at(MonsterList *head, MonsterList *key);
void destroy_mlist(MonsterList **head);
void cull_mlist(MonsterList *head);


#endif
