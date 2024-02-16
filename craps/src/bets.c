#include "bets.h"
#include "colors.h"
#include "node.h"

#include <stdio.h>

double getPassOddsPayout(int point) {
    switch (point) {
        case 4:
        case 10:
            return (2/1);
        case 5:
        case 9:
            return (3/2);
        case 6:
        case 8:
            return (6/5);
    }
}

double getDontPassOddsPayout(int point) {
    switch (point) {
        case 4:
        case 10:
            return (1/2);
        case 5:
        case 9:
            return (2/3);
        case 6:
        case 8:
            return (5/6);
    }
}

void winOnPass(struct Player** mainPlayer, struct Node **computerHead, int point) {
    if ((*mainPlayer)->chipsOnPass != 0) {
        printf("%sYou doubled your %d chips on the pass line!\nYou took back all your chips on the pass line.\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnPass, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnPass * 2;
        (*mainPlayer)->chipsOnPass = 0;
    }
    if ((*mainPlayer)->chipsOnPassOdds != 0) {
        printf("%sYou won the pass odds!\n%s", ANSI_GREEN, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnPassOdds + (getPassOddsPayout(point) * (*mainPlayer)->chipsOnPassOdds);
        (*mainPlayer)->chipsOnPassOdds = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnPass != 0) {
            printf("%s%s doubled their %d chips on the pass line!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnPass, ANSI_RESET);
            last->player->chips += last->player->chipsOnPass * 2;
            last->player->chipsOnPass = 0;
        }
        if (last->player->chipsOnPassOdds != 0) {
            printf("%s%s won the pass odds!\n%s", 
                ANSI_PURPLE, last->player->name, ANSI_RESET);
            last->player->chips += last->player->chipsOnPassOdds + (getPassOddsPayout(point) * last->player->chipsOnPassOdds);
            last->player->chipsOnPassOdds = 0;
        }
        last = last->next;
    }
}

void loseOnPass(struct Player** mainPlayer, struct Node **computerHead, int point) {
    if ((*mainPlayer)->chipsOnPass != 0) {
        printf("%sYou lost your %d chips on the pass line!\n%s", ANSI_RED, (*mainPlayer)->chipsOnPass, ANSI_RESET);
        (*mainPlayer)->chipsOnPass = 0;
    }
    if ((*mainPlayer)->chipsOnPassOdds != 0) {
        printf("%sYou lost the pass odds!\n%s", ANSI_RED, ANSI_RESET);
        (*mainPlayer)->chipsOnPassOdds = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnPass != 0) {
            printf("%s%s lost their %d chips on the pass line!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnPass, ANSI_RESET);
            last->player->chipsOnPass = 0;
        }
        if ((*mainPlayer)->chipsOnPassOdds != 0) {
            printf("%s%s lost the pass odds!\n%s", 
                ANSI_PURPLE, last->player->chipsOnPass, ANSI_RESET);
            last->player->chipsOnPassOdds = 0;
        }
        last = last->next;
    }
}

void winOnDontPass(struct Player** mainPlayer, struct Node **computerHead, int point) {
    if ((*mainPlayer)->chipsOnDontPass != 0) {
        printf("%sYou doubled your %d chips on the don't pass line!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnDontPass, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnDontPass * 2;
        (*mainPlayer)->chipsOnDontPass = 0;
    }
    if ((*mainPlayer)->chipsOnDontPassOdds != 0) {
        printf("%sYou won the don't pass odds!\n%s", ANSI_GREEN, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnDontPassOdds + (getDontPassOddsPayout(point) * (*mainPlayer)->chipsOnDontPassOdds);
        (*mainPlayer)->chipsOnDontPassOdds = 0;
    }
    struct Node *last = *computerHead;
    while (last != NULL) {
        if (last->player->chipsOnDontPass != 0) {
            printf("%s%s doubled their %d chips on the don't pass line!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnDontPass, ANSI_RESET);
            last->player->chips += last->player->chipsOnDontPass * 2;
            last->player->chipsOnDontPass = 0;
        }
        if ((*mainPlayer)->chipsOnDontPassOdds != 0) {
            printf("%s%s won the don't pass odds!\n%s", 
                ANSI_PURPLE, last->player->name, ANSI_RESET);
            last->player->chips += last->player->chipsOnDontPassOdds + (getDontPassOddsPayout(point) * last->player->chipsOnDontPassOdds);
            last->player->chipsOnDontPassOdds = 0;
        }
        last = last->next;
    }
}

void loseOnDontPass(struct Player** mainPlayer, struct Node **computerHead, int point) {
    if ((*mainPlayer)->chipsOnDontPass != 0) {
        printf("%sYou lost your %d chips on the don't pass line!\n%s", ANSI_RED, (*mainPlayer)->chipsOnDontPass, ANSI_RESET);
        (*mainPlayer)->chipsOnDontPass = 0;
    }
    if ((*mainPlayer)->chipsOnDontPassOdds != 0) {
        printf("%sYou lost the don't pass odds!\n%s", ANSI_RED, ANSI_RESET);
        (*mainPlayer)->chipsOnDontPassOdds = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnDontPass != 0) {
            printf("%s%s lost their %d chips on the don't pass line!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnDontPass, ANSI_RESET);
            last->player->chipsOnDontPass = 0;
        }
        if (last->player->chipsOnDontPassOdds != 0) {
            printf("%s%s lost the don't pass odds!\n%s", 
                ANSI_PURPLE, last->player->name, ANSI_RESET);
            last->player->chipsOnDontPassOdds = 0;
        }
        last = last->next;
    }
}

void winOnBig6(struct Player** mainPlayer, struct Node **computerHead) {
    if ((*mainPlayer)->chipsOnBigSix != 0) {
        printf("%sYou doubled your %d chips on the big 6!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnBigSix, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnBigSix * 2;
        (*mainPlayer)->chipsOnBigSix = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnBigSix != 0) {
            printf("%s%s doubled their %d chips on the big 6!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnBigSix, ANSI_RESET);
            last->player->chips += last->player->chipsOnBigSix * 2;
            last->player->chipsOnBigSix = 0;
        }
        last = last->next;
    }
}

void loseOnBig6(struct Player** mainPlayer, struct Node **computerHead) {
    if ((*mainPlayer)->chipsOnBigSix != 0) {
        printf("%sYou lost your %d chips on the big 6!\n%s", ANSI_RED, (*mainPlayer)->chipsOnBigSix, ANSI_RESET);
        (*mainPlayer)->chipsOnBigSix = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnBigSix != 0) {
            printf("%s%s lost their %d chips on the big 6!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnBigSix, ANSI_RESET);
            last->player->chipsOnBigSix = 0;
        }
        last = last->next;
    }
}

void winOnBig8(struct Player** mainPlayer, struct Node **computerHead) {
    if ((*mainPlayer)->chipsOnBigEight != 0) {
        printf("%sYou doubled your %d chips on the big 8!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnBigEight, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnBigEight * 2;
        (*mainPlayer)->chipsOnBigEight = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnBigEight != 0) {
            printf("%s%s doubled their %d chips on the big 8!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnBigEight, ANSI_RESET);
            last->player->chips += last->player->chipsOnBigEight * 2;
            last->player->chipsOnBigEight = 0;
        }
        last = last->next;
    }
}

void loseOnBig8(struct Player** mainPlayer, struct Node **computerHead) {
    if ((*mainPlayer)->chipsOnBigEight != 0) {
        printf("%sYou lost your %d chips on the big 8!\n%s", ANSI_RED, (*mainPlayer)->chipsOnBigEight, ANSI_RESET);
        (*mainPlayer)->chipsOnBigEight = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnBigEight != 0) {
            printf("%s%s lost their %d chips on the big 8!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnBigEight, ANSI_RESET);
            last->player->chipsOnBigEight = 0;
        }
        last = last->next;
    }
}

void loseOnField(struct Player** mainPlayer, struct Node **computerHead) {
    printf("The field has lost!\n");
    (*mainPlayer)->chipsOnField2 = 0;
    (*mainPlayer)->chipsOnField3 = 0;
    (*mainPlayer)->chipsOnField4 = 0;
    (*mainPlayer)->chipsOnField9 = 0;
    (*mainPlayer)->chipsOnField10 = 0;
    (*mainPlayer)->chipsOnField11 = 0;
    (*mainPlayer)->chipsOnField12 = 0;
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        last->player->chipsOnField2 = 0;
        last->player->chipsOnField3 = 0;
        last->player->chipsOnField4 = 0;
        last->player->chipsOnField9 = 0;
        last->player->chipsOnField10 = 0;
        last->player->chipsOnField11 = 0;
        last->player->chipsOnField12 = 0;
        last = last->next;
    }
}

void winOnField2(struct Player** mainPlayer, struct Node **computerHead){
    if ((*mainPlayer)->chipsOnField2 != 0) {
        printf("%sYou doubled your %d chips on field (2)!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnField2, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnField2 * 3;
        (*mainPlayer)->chipsOnField2 = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnField2 != 0) {
            printf("%s%s doubled their %d chips on field (2)!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnField2, ANSI_RESET);
            last->player->chips += last->player->chipsOnField2 * 3;
            last->player->chipsOnField2 = 0;
        }
        last = last->next;
    }
}

void winOnField3(struct Player** mainPlayer, struct Node **computerHead){
    if ((*mainPlayer)->chipsOnField3 != 0) {
        printf("%sYou doubled your %d chips on field (3)!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnField3, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnField3 * 2;
        (*mainPlayer)->chipsOnField3 = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnField3 != 0) {
            printf("%s%s doubled their %d chips on field (3)!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnField3, ANSI_RESET);
            last->player->chips += last->player->chipsOnField3 * 2;
            last->player->chipsOnField3 = 0;
        }
        last = last->next;
    }
}

void winOnField4(struct Player** mainPlayer, struct Node **computerHead){
    if ((*mainPlayer)->chipsOnField4 != 0) {
        printf("%sYou doubled your %d chips on field (4)!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnField4, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnField4 * 2;
        (*mainPlayer)->chipsOnField4 = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnField4 != 0) {
            printf("%s%s doubled their %d chips on field (4)!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnField4, ANSI_RESET);
            last->player->chips += last->player->chipsOnField4 * 2;
            last->player->chipsOnField4 = 0;
        }
        last = last->next;
    }
}

void winOnField9(struct Player** mainPlayer, struct Node **computerHead){
    if ((*mainPlayer)->chipsOnField9 != 0) {
        printf("%sYou doubled your %d chips on field (9)!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnField9, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnField9 * 2;
        (*mainPlayer)->chipsOnField9 = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnField9 != 0) {
            printf("%s%s doubled their %d chips on field (9)!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnField9, ANSI_RESET);
            last->player->chips += last->player->chipsOnField9 * 2;
            last->player->chipsOnField9 = 0;
        }
        last = last->next;
    }
}

void winOnField10(struct Player** mainPlayer, struct Node **computerHead){
    if ((*mainPlayer)->chipsOnField10 != 0) {
        printf("%sYou doubled your %d chips on field (10)!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnField10, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnField10 * 2;
        (*mainPlayer)->chipsOnField10 = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnField10 != 0) {
            printf("%s%s doubled their %d chips on field (10)!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnField10, ANSI_RESET);
            last->player->chips += last->player->chipsOnField10 * 2;
            last->player->chipsOnField10 = 0;
        }
        last = last->next;
    }
}

void winOnField11(struct Player** mainPlayer, struct Node **computerHead){
    if ((*mainPlayer)->chipsOnField11 != 0) {
        printf("%sYou doubled your %d chips on field (11)!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnField11, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnField11 * 2;
        (*mainPlayer)->chipsOnField11 = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnField11 != 0) {
            printf("%s%s doubled their %d chips on field (11)!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnField11, ANSI_RESET);
            last->player->chips += last->player->chipsOnField11 * 2;
            last->player->chipsOnField11 = 0;
        }
        last = last->next;
    }
}

void winOnField12(struct Player** mainPlayer, struct Node **computerHead){
    if ((*mainPlayer)->chipsOnField12 != 0) {
        printf("%sYou doubled your %d chips on field (12)!\n%s", ANSI_GREEN, (*mainPlayer)->chipsOnField12, ANSI_RESET);
        (*mainPlayer)->chips += (*mainPlayer)->chipsOnField12 * 3;
        (*mainPlayer)->chipsOnField12 = 0;
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (last->player->chipsOnField12 != 0) {
            printf("%s%s doubled their %d chips on field (12)!\n%s", 
                ANSI_PURPLE, last->player->name, last->player->chipsOnField12, ANSI_RESET);
            last->player->chips += last->player->chipsOnField12 * 3;
            last->player->chipsOnField12 = 0;
        }
        last = last->next;
    }
}


void roll2(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (isComeOut) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnField2(mainPlayer, computerHead);
}

void roll3(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (isComeOut) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnField3(mainPlayer, computerHead);
}

void roll4(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (point == 4) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnField4(mainPlayer, computerHead);
}

void roll5(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (point == 5) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    loseOnField(mainPlayer, computerHead);
}

void roll6(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (point == 6) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnBig6(mainPlayer, computerHead);
    loseOnField(mainPlayer, computerHead);
}

void roll7(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (isComeOut) {
        winOnPass(mainPlayer, computerHead, point);
        loseOnDontPass(mainPlayer, computerHead, point);
    } else {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    loseOnBig6(mainPlayer, computerHead);
    loseOnBig8(mainPlayer, computerHead);
    loseOnField(mainPlayer, computerHead);
}

void roll8(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (point == 8) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnBig8(mainPlayer, computerHead);
    loseOnField(mainPlayer, computerHead);
}

void roll9(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (point == 9) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnField9(mainPlayer, computerHead);
}

void roll10(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (point == 10) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnField10(mainPlayer, computerHead);
}

void roll11(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (isComeOut) {
        winOnPass(mainPlayer, computerHead, point);
        loseOnDontPass(mainPlayer, computerHead, point);
    }
    winOnField11(mainPlayer, computerHead);
}

void roll12(struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    if (isComeOut) {
        winOnDontPass(mainPlayer, computerHead, point);
        loseOnPass(mainPlayer, computerHead, point);
    }
    winOnField12(mainPlayer, computerHead);
}

void roll(int total, struct Player** mainPlayer, struct Node **computerHead, bool isComeOut, int point) {
    switch (total) {
        case 2:
            roll2(mainPlayer, computerHead, isComeOut, point);
            break;
        case 3:
            roll3(mainPlayer, computerHead, isComeOut, point);
            break;
        case 4:
            roll4(mainPlayer, computerHead, isComeOut, point);
            break;
        case 5:
            roll5(mainPlayer, computerHead, isComeOut, point);
            break;
        case 6:
            roll6(mainPlayer, computerHead, isComeOut, point);
            break;
        case 7:
            roll7(mainPlayer, computerHead, isComeOut, point);
            break;
        case 8:
            roll8(mainPlayer, computerHead, isComeOut, point);
            break;
        case 9:
            roll9(mainPlayer, computerHead, isComeOut, point);
            break;
        case 10:
            roll10(mainPlayer, computerHead, isComeOut, point);
            break;
        case 11:
            roll11(mainPlayer, computerHead, isComeOut, point);
            break;
        case 12:
            roll12(mainPlayer, computerHead, isComeOut, point);
            break;
    }
}