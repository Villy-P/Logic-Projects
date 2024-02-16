#ifndef __C_CRAPS_SRC_LINKEDLIST_H__
#define __C_CRAPS_SRC_LINKEDLIST_H__

#include "node.h"

struct LinkedList {
    struct Node *head;
};

struct LinkedList* createNewLinkedList();
void addToLinkedList(struct Node **head, struct Node *node);
void deleteFromLinkedList(struct Node **head, struct Node *node);

#endif