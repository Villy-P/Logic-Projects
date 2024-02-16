#ifndef __C_CRAPS_SRC_NODE_H__
#define __C_CRAPS_SRC_NODE_H__

#include "player.h"

struct Node {
    struct Player *player;
    struct Node *next;
};

struct Node *newNode(struct Player *player);

#endif