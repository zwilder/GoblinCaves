#include <goblincaves.h>

const int MIN_ROOM_SIZE = 5;

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
    } else if(NULL == node->leftChild) {
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
    if(max < MIN_ROOM_SIZE) {
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
        node->leftChild = new_node(leftRect);
        node->rightChild = new_node(rightRect);
    } else {
        leftRect = make_rect(node->data.pos.x,
                             node->data.pos.y, 
                             node->data.dim.x,
                             split);
        rightRect = make_rect(node->data.pos.x,
                              node->data.pos.y + split,
                              node->data.dim.x,
                              node->data.dim.y - split);
        node->leftChild = new_node(leftRect);
        node->rightChild = new_node(rightRect);
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
    Vec2i leftCenter, rightCenter;
    if(NULL == node) {
        return;
    }
    connect_leaves(node->leftChild);
    if(NULL != node->leftChild) {
        place_corridor(get_center(node->leftChild->data),
                       get_center(node->rightChild->data));
    }
}
void make_rooms_in_leaves(Node *node) {
    int x,y,w,h;
    Vec2i center;
    if(NULL == node) {
        return;
    }
    if(NULL == node->leftChild) {
        /* Make rooms */
        /* Left */
        center = get_center(node->leftChild->data);
        w = mt_rand(MIN_ROOM_SIZE, node->leftChild->data.dim.x);
        h = mt_rand(MIN_ROOM_SIZE, node->leftChild->data.dim.y);
        x = center.x - (w / 2);
        y = center.y - (h / 2);
        place_room(make_rect(x,y,w,h));
        /* Right */
        center = get_center(node->rightChild->data);
        w = mt_rand(MIN_ROOM_SIZE, node->rightChild->data.dim.x);
        h = mt_rand(MIN_ROOM_SIZE, node->rightChild->data.dim.y);
        x = center.x - (w / 2);
        y = center.y - (h / 2);
        place_room(make_rect(x,y,w,h));
    }
    make_rooms_in_leaves(node->leftChild);
    make_rooms_in_leaves(node->rightChild);
}

void make_bsp_dungeon(void) {
    Rect rootRect = make_rect(0,0,MAP_WIDTH,MAP_HEIGHT);
    Node *root = new_node(rootRect);
    /* Make tree */
    /* Needs recursion, this is silly brute force haha */
    /* 1st iteration */
    split_node(root); 
    /* 2nd iteration */
    split_node(root->leftChild);
    split_node(root->rightChild);
    /* 3rd iteration */
    split_node(root->leftChild->leftChild);
    split_node(root->leftChild->rightChild);
    split_node(root->rightChild->leftChild);
    split_node(root->rightChild->rightChild);
    /* 4th iteration */
    split_node(root->leftChild->leftChild->leftChild);
    split_node(root->leftChild->leftChild->rightChild);
    split_node(root->leftChild->rightChild->leftChild);
    split_node(root->leftChild->rightChild->rightChild);
    split_node(root->rightChild->leftChild->leftChild);
    split_node(root->rightChild->leftChild->rightChild);
    split_node(root->rightChild->rightChild->leftChild);
    split_node(root->rightChild->rightChild->rightChild);

    /* Place rooms in leaves */
    make_rooms_in_leaves(root);

    /* Connect rooms */
    connect_leaves(root);

    /* Place stairs */
    
    /* Place player */
    /* Place enemies */
    /* Place pickups */
}
