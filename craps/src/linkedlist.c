#include "linkedlist.h"

struct LinkedList* createNewLinkedList() {
    struct LinkedList *list = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    list->head = NULL;
    return list;
}

void addToLinkedList(struct Node **head, struct Node *node) {
    struct Node *last = *head;
    if (*head == NULL) {
        *head = node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = node;
}

void deleteFromLinkedList(struct Node **head, struct Node *node) {
    struct Node *temp = *head, *prev;
    if (temp != NULL && strcmp(temp->player->name, node->player->name) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->player->name, node->player->name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}