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
