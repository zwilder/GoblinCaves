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
