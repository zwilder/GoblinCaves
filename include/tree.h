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
#ifndef TREE_H
#define TREE_H

struct Node {
    Rect data;
    struct Node* leftChild;
    struct Node* rightChild;
};

typedef struct Node Node;

/******************
 * tree.c functions
 ******************/
Node* new_node(Rect data);
void make_bsp_dungeon(void); 
void make_rooms_in_leaves(Node *node);
void connect_leaves(Node *node);
int count_leaves(Node *node);
bool split_node(Node *node);
void split_tree(Node *node);
void destroy_node(Node* node);

#endif
