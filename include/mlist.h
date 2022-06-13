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
#ifndef MLIST_H
#define MLIST_H

/*
 * This could (should?) probably be modified to be a skip list, where the skip
 * pointer would point to the next locID (lvl)
 */
struct MList {
    Monster *data;
    struct MList *next;
    struct MList *prev;
};

typedef struct MList MList;

MList* create_mlist(Monster *data);
void push_mlist(MList **head, Monster *data);
void transfer_mlist(MList **from, MList **to, Monster *data);
Monster* find_mlist(MList *head, int flags);
Monster* monster_at_pos(MList *head, Vec2i pos, int locID);
void sort_mlist(MList **head);
int count_mlist(MList *head);
void destroy_mlist(MList **head);
void destroy_mlist_node(MList **head, MList *del);
void destroy_mlist_monster(MList **head, Monster *target);

#endif
