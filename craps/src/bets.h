#ifndef __C_CRAPS_SRC_BETS_H__
#define __C_CRAPS_SRC_BETS_H__

#include "player.h"
#include "node.h"

void roll(int total, struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);

double getPassOddsPayout(int point);
double getDontPassOddsPayout(int point);

void winOnPass(struct Player** mainPlayer, struct Node **computerHead, int point);
void loseOnPass(struct Player** mainPlayer, struct Node **computerHead, int point);
void winOnDontPass(struct Player** mainPlayer, struct Node **computerHead, int point);
void loseOnDontPass(struct Player** mainPlayer, struct Node **computerHead, int point);

void winOnBig6(struct Player** mainPlayer, struct Node **computerHead);
void loseOnBig6(struct Player** mainPlayer, struct Node **computerHead);
void winOnBig8(struct Player** mainPlayer, struct Node **computerHead);
void loseOnBig8(struct Player** mainPlayer, struct Node **computerHead);

void loseOnField(struct Player** mainPlayer, struct Node **computerHead);

void winOnField2(struct Player** mainPlayer, struct Node **computerHead);
void winOnField3(struct Player** mainPlayer, struct Node **computerHead);
void winOnField4(struct Player** mainPlayer, struct Node **computerHead);
void winOnField9(struct Player** mainPlayer, struct Node **computerHead);
void winOnField10(struct Player** mainPlayer, struct Node **computerHead);
void winOnField11(struct Player** mainPlayer, struct Node **computerHead);
void winOnField12(struct Player** mainPlayer, struct Node **computerHead);

void roll2(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll3(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll4(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll5(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll6(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll7(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll8(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll9(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll10(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll11(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);
void roll12(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point);

#endif