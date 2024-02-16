#include "player.h"

struct Player* newPlayer(char *name, int cash, int chips, bool isMainPlayer) {
    struct Player *p = (struct Player*) malloc(sizeof(struct Player));
    strcpy(p->name, name);
    p->cash = cash;
    p->chips = chips;
    p->isMainPlayer = isMainPlayer;
    p->chipsOnPass = 0;
    p->chipsOnDontPass = 0;
    p->chipsOnPassOdds = 0;
    p->chipsOnDontPassOdds = 0;
    p->chipsOnBigSix = 0;
    p->chipsOnBigEight = 0;
    p->chipsOnField2 = 0;
    p->chipsOnField3 = 0;
    p->chipsOnField4 = 0;
    p->chipsOnField9 = 0;
    p->chipsOnField10 = 0;
    p->chipsOnField11 = 0;
    p->chipsOnField12 = 0;
    return p;
}