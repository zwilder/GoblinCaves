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


Node* new_node(Rect data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

void destroy_node(Node* node) {
    if(NULL == node) {
        return;
    }
    destroy_node(node->leftChild);
    destroy_node(node->rightChild);
    free(node);
}

bool split_node(Node *node) {
    int max, split;
    Rect leftRect, rightRect;
    bool horiz = mt_bool(); /*Split horizontally?*/

    /* Check if node is blank, or if there is already data in the children */
    if(NULL == node) {
        return false;
    } 
    /* If splitting horizontally, the max size will be the rooms width - min
     * room size, otherwise the max size will be the rooms height - min size*/
    if(horiz) {
        max = node->data.dim.x - MIN_ROOM_SIZE;
    } else {
        max = node->data.dim.y - MIN_ROOM_SIZE;
    }
    /* If the max turns out to be less than the minimum, splitting failed */
    if(max <= MIN_ROOM_SIZE) {
        return false;
    }

    /* Choose a random point between the minimum room size and the maximum room
     * size */
    split = mt_rand(MIN_ROOM_SIZE, max);

    if(horiz) {
        leftRect = make_rect(node->data.pos.x,
                             node->data.pos.y, 
                             split,
                             node->data.dim.y);
        rightRect = make_rect(node->data.pos.x + split,
                              node->data.pos.y,
                              node->data.dim.x - split,
                              node->data.dim.y);
        if(leftRect.dim.x >= MIN_ROOM_SIZE &&
           leftRect.dim.y >= MIN_ROOM_SIZE){
            node->leftChild = new_node(leftRect);
        }
        if(rightRect.dim.x >= MIN_ROOM_SIZE &&
           rightRect.dim.y >= MIN_ROOM_SIZE){
            node->rightChild = new_node(rightRect);
        }
    } else {
        leftRect = make_rect(node->data.pos.x,
                             node->data.pos.y, 
                             node->data.dim.x,
                             split);
        rightRect = make_rect(node->data.pos.x,
                              node->data.pos.y + split,
                              node->data.dim.x,
                              node->data.dim.y - split);
        if(leftRect.dim.x >= MIN_ROOM_SIZE &&
           leftRect.dim.y >= MIN_ROOM_SIZE){
            node->leftChild = new_node(leftRect);
        }
        if(rightRect.dim.x >= MIN_ROOM_SIZE &&
           rightRect.dim.y >= MIN_ROOM_SIZE){
            node->rightChild = new_node(rightRect);
        }
    }

    return true;
}

/*
 *            1
 *         /     \
 *        2       3
 *       / \     / \
 *      4   5    N  N
 *     / \ / \
 *    N  N N  N
 */
void visit_postorder(Node *node) {
    /* Visits 4 5 2 3 1 */
    if(NULL == node) {
        return;
    }

    visit_postorder(node->leftChild);
    visit_postorder(node->rightChild);
    /* Do something here */
}

void connect_leaves(Node *node) {
/*
 *            1
 *         /     \
 *        2       3
 *       / \     / \
 *      4   5    N  N
 *     / \ / \
 *    N  N N  N
 */
    Vec2i leftCenter, rightCenter;
    if(NULL == node) {
        /* Empty node */
        return;
    }
    if(NULL == node->leftChild || NULL == node->rightChild) {
        /* Leaf node 4,5,3 */
        return;
    }
    if(NULL == node->leftChild->leftChild || NULL == node->leftChild->rightChild ||
            NULL == node->rightChild->leftChild || NULL == node->rightChild->rightChild) {
        /* Nodes 2,1 */
        leftCenter = get_center(node->leftChild->data);
        rightCenter = get_center(node->rightChild->data);
        place_corridor(leftCenter, rightCenter);
    }
    /*
    
    leftCenter = get_center(node->leftChild->data);
    rightCenter = get_center(node->rightChild->data);
    place_corridor(leftCenter, rightCenter);
        */

    connect_leaves(node->leftChild);
    connect_leaves(node->rightChild);
}

int count_leaves(Node *node) {
    if(NULL == node) {
        return 0;
    }
    if(NULL == node->leftChild && NULL == node->rightChild) {
        return 1;
    } else {
        return count_leaves(node->leftChild) + count_leaves(node->rightChild);
    }
}

void make_rooms_in_leaves(Node *node) {
    int x,y,w,h;
    if(NULL == node) {
        return;
    }
    if(NULL == node->leftChild || NULL == node->rightChild) {
        /* Make rooms */
        w = mt_rand(MIN_ROOM_SIZE, node->data.dim.x);
        h = mt_rand(MIN_ROOM_SIZE, node->data.dim.y);
        x = node->data.pos.x;
        y = node->data.pos.y;
        if(((x + w) > MAP_WIDTH) || (w > node->data.dim.x)) {
            w = node->data.dim.x;
        }
        if(((y + h) > MAP_HEIGHT) || (h > node->data.dim.y)) {
            h = node->data.dim.y;
        }
        if(w > MAX_ROOM_SIZE) {
            w = MAX_ROOM_SIZE;
        }
        if(h > MAX_ROOM_SIZE) {
            h = MAX_ROOM_SIZE;
        }
        place_room(make_rect(x,y,w,h));
    }
    make_rooms_in_leaves(node->leftChild);
    make_rooms_in_leaves(node->rightChild);
}

void split_tree(Node *node) {
    if(NULL == node) {
        return;
    }
    if(split_node(node)) {
        split_tree(node->leftChild);
        split_tree(node->rightChild);
    }
}

void make_bsp_dungeon(void) {
    Rect rootRect = make_rect(0,0,MAP_WIDTH - 1,MAP_HEIGHT - 1);
    Node *root = new_node(rootRect);
    int x,y, numRooms;
    /* Make tree */
    numRooms = 0;
    while(numRooms < MIN_NUM_ROOMS) {
        split_tree(root);
        numRooms = count_leaves(root);
        if(numRooms < MIN_NUM_ROOMS) {
            destroy_node(root);
            root = new_node(rootRect);
            write_log("Num of leaves < min num rooms, trying again!");
        }
    }

    /* Fill with walls */
    for(x = 0; x < MAP_WIDTH; x++) {
        for(y = 0; y < MAP_HEIGHT; y++) {
            place_tile(make_vec(x,y), TILE_WALL);
        }
    }
    
    /* Place rooms in leaves */
    make_rooms_in_leaves(root);


    /* Connect rooms */
    connect_leaves(root);

    /* Place stairs */
    /* Place player */
    /* Place enemies */
    /* Place pickups */

    /* Cleanup */
    destroy_node(root);
}
