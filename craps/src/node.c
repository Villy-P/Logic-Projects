#include "node.h"

struct Node *newNode(struct Player *player) {
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node->player = player;
    node->next = NULL;
    return node;
}