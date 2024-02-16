#ifndef __C_CRAPS_SRC_PLAYER_H__
#define __C_CRAPS_SRC_PLAYER_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Player {
    char name[256];
    int cash;
    int chips;
    bool isMainPlayer;
    int chipsOnPass;
    int chipsOnDontPass;
    int chipsOnPassOdds;
    int chipsOnDontPassOdds;
    int chipsOnBigSix;
    int chipsOnBigEight;
    int chipsOnField2;
    int chipsOnField3;
    int chipsOnField4;
    int chipsOnField9;
    int chipsOnField10;
    int chipsOnField11;
    int chipsOnField12;
};

struct Player* newPlayer(char *name, int cash, int chips, bool isMainPlayer);

#endif