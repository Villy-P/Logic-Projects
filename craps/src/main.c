#include "player.h"
#include "colors.h"
#include "input.h"
#include "board.h"
#include "linkedlist.h"
#include "node.h"
#include "random.h"
#include "strings.h"
#include "bets.h"

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool hasChips(struct Player *player) {
    return ((player->chips) > 0 ||
           (player->chipsOnPass > 0) ||
           (player->chipsOnDontPass) > 0 ||
           (player->chipsOnPassOdds) > 0 ||
           (player->chipsOnDontPassOdds) > 0 ||
           (player->chipsOnBigSix) > 0 ||
           (player->chipsOnBigEight) > 0 ||
           (player->chipsOnField2) > 0 ||
           (player->chipsOnField3) > 0 ||
           (player->chipsOnField4) > 0 ||
           (player->chipsOnField9) > 0 ||
           (player->chipsOnField10) > 0 ||
           (player->chipsOnField11) > 0 ||
           (player->chipsOnField12) > 0);
}

void broke(struct Player** mainPlayer, struct Node **computerHead) {
    if (!hasChips(&(**mainPlayer))) {
        printf("%sYou are broke.%s\n");
        getStringInput("Press enter to exit.\n");
        exit(0);
    }
    struct Node *last = *computerHead;
    while (last->next != NULL) {
        if (!hasChips(&(*last->player))) {
            printf("%s%s has gone broke!%s\n", ANSI_RED, last->player->name, ANSI_RESET);
            deleteFromLinkedList(&(*computerHead), &(*last));
            broke(mainPlayer, computerHead);
        }
        last = last->next;
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    struct Player* mainPlayer = newPlayer("", 0, 0, true);
    printf("%sWelcome to Craps!%s\n", ANSI_BLUE, ANSI_RESET);
    printf("%sPlease enter your name.%s\n", ANSI_GREEN, ANSI_RESET);
    strcpy(mainPlayer->name, getStringInput(">"));
    system("cls");
    printf("%sHow much cash did you bring?%s\n", ANSI_MAGENTA, ANSI_RESET);
    mainPlayer->cash = getIntInput(">", 1, INT_MAX);
    while (true) {
        printf("%sHow many computers do you want to play against? (0-19)%s\n", ANSI_PURPLE, ANSI_RESET);
        const int numOfComputers = getIntInput(">", 0, 19);
        struct LinkedList* computers = createNewLinkedList();
        for (int i = 0; i < numOfComputers; i++) {
            char computerHashtag[] = "Computer #";
            char iAsString[12];
            sprintf(iAsString, "%d", i);
            char *computerName = concat(computerHashtag, iAsString);
            struct Player* computer = newPlayer(computerName, 0, 1500, false);
            struct Node *computerNode = newNode(computer);
            addToLinkedList(&computers->head, computerNode);
        }
        printf("%sYou go to another table to play some more craps.%s\n", ANSI_ORANGE, ANSI_RESET);
        printf("%sYou trade in $%d for some chips.%s\n", ANSI_CYAN, mainPlayer->cash, ANSI_RESET);
        mainPlayer->chips = mainPlayer->cash;
        mainPlayer->cash = 0;
        struct Player** shooter = &mainPlayer;
        COME:
        while (true) {
            printf("%sIt is time for the come out roll%s\n", ANSI_PURPLE, ANSI_RESET);
            printf("%sThe stickman passes you five die.%s\n", ANSI_BLUE, ANSI_RESET);
            printf("%sYou pick up two die.%s\n", ANSI_YELLOW, ANSI_RESET);
            printf("%sEnter the amount of chips you want to place down. (You have %d chips)%s\n", ANSI_BLUE, (*shooter)->chips, ANSI_RESET);
            int chipsToPlace = getIntInput(">", 1, mainPlayer->chips);
            printf("%sWhere do you want to place them?%s\n", ANSI_DARK_CYAN, ANSI_RESET);
            printf("%s1: Pass%s\n", ANSI_BROWN, ANSI_RESET);
            printf("%s2: Don't Pass%s\n", ANSI_GREEN, ANSI_RESET);
            int choice = getIntInput(">", 1, 2);
            mainPlayer->chips -= chipsToPlace;
            if (choice == 1)
                mainPlayer->chipsOnPass += chipsToPlace;
            else
                mainPlayer->chipsOnDontPass += chipsToPlace;
            printf("%sThe computers will now place their bets.%s\n", ANSI_DARK_CYAN, ANSI_RESET);
            struct Node *currentComputer = computers->head;
            while (currentComputer != NULL) {
                int randomValue = randomInRange(0, 10);
                int chipsToPlaceDown = randomInRange(250, 750);
                if (randomValue <= 5 && currentComputer->player->chips >= chipsToPlaceDown) { // Bet on pass
                    printf("%s%s placed %d $1 chips on the pass line.%s\n", ANSI_BLUE, currentComputer->player->name, chipsToPlaceDown, ANSI_RESET);
                    currentComputer->player->chips -= chipsToPlaceDown;
                    currentComputer->player->chipsOnPass = chipsToPlaceDown;
                } else if (randomValue <= 8 && currentComputer->player->chips >= chipsToPlaceDown) { // Bet on dont pass
                    printf("%s%s placed %d $1 chips on the don't pass line.%s\n", ANSI_BLUE, currentComputer->player->name, chipsToPlaceDown, ANSI_RESET);
                    currentComputer->player->chips -= chipsToPlaceDown;
                    currentComputer->player->chipsOnDontPass = chipsToPlaceDown;
                } else {
                    printf("%s%s did not place any chips down.%s\n", ANSI_BLUE, currentComputer->player->name, ANSI_RESET);
                }
                currentComputer = currentComputer->next;
            }
            int firstRoll = randomInRange(1, 6);
            int secondRoll = randomInRange(1, 6);
            int total = firstRoll + secondRoll;
            printf("%s%s rolls the die...%s\n", ANSI_BLUE, (*shooter)->name, ANSI_RESET);
            printf("%sThe die hit the back table...%s\n", ANSI_GREEN, ANSI_RESET);
            printf("%s+---+ +---+%s\n", ANSI_ORANGE, ANSI_RESET);
            printf("%s+ %d + + %d +%s\n", ANSI_ORANGE, firstRoll, secondRoll, ANSI_RESET);
            printf("%s+---+ +---+%s\n", ANSI_ORANGE, ANSI_RESET);
            if (total == 7 || total == 11) {
                printf("%sThe total is %d! The pass line wins and the don't pass line loses!%s\n", ANSI_GREEN, total, ANSI_RESET);
                roll(total, &mainPlayer, &computers->head, true, 0);
                continue;
            } else if (total == 2 || total == 3 || total == 12) {
                printf("%sThe total is %d! The don't pass line wins and the pass line loses!%s\n", ANSI_GREEN, total, ANSI_RESET);
                roll(total, &mainPlayer, &computers->head, true, 0);
                continue;
            }
            int point = total;
            printf("%sThe total is %d! The point has been established.%s\n", ANSI_GREEN, total, ANSI_RESET);
            WHILE:
            while (true) {
                while (true) {
                    broke(&mainPlayer, &computers->head);
                    printf("%sPick a bet.%s\n", ANSI_PURPLE, ANSI_RESET);
                    printf("%s1: Pass Odds (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnPassOdds, ANSI_RESET);
                    printf("%s2: Don't Pass Odds (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnDontPassOdds, ANSI_RESET);
                    printf("%s3: Big 6 (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnBigSix, ANSI_RESET);
                    printf("%s4: Big 8 (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnBigEight, ANSI_RESET);
                    printf("%s5: Field (2) (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnField2, ANSI_RESET);
                    printf("%s6: Field (3) (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnField3, ANSI_RESET);
                    printf("%s7: Field (4) (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnField4, ANSI_RESET);
                    printf("%s8: Field (9) (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnField9, ANSI_RESET);
                    printf("%s9: Field (10) (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnField10, ANSI_RESET);
                    printf("%s10: Field (11) (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnField11, ANSI_RESET);
                    printf("%s11: Field (12) (Current: %d)%s\n", ANSI_BLUE, mainPlayer->chipsOnField12, ANSI_RESET);
                    int betInput = getIntInput(">", 1, 11);
                    printf("%sEnter the amount of chips you wish to play. You have %d chips.%s\n", ANSI_GREEN, mainPlayer->chips, ANSI_RESET);
                    switch (getIntInput(">", 1, 1)) {
                        case 1:
                            if (mainPlayer->chipsOnPass == 0) {
                                printf("%sYou have no chips on the pass line.%s", ANSI_RED, ANSI_RESET);
                                goto WHILE;
                            }
                            mainPlayer->chipsOnPassOdds = betInput;
                            break;
                        case 2:
                            if (mainPlayer->chipsOnDontPass == 0) {
                                printf("%sYou have no chips on the don't pass line.%s", ANSI_RED, ANSI_RESET);
                                goto WHILE;
                            }
                            mainPlayer->chipsOnDontPassOdds = betInput;
                            break;
                        case 3:
                            mainPlayer->chipsOnBigSix = betInput;
                            break;
                        case 4:
                            mainPlayer->chipsOnBigEight = betInput;
                            break;
                        case 5:
                            mainPlayer->chipsOnField2 = betInput;
                            break;
                        case 6:
                            mainPlayer->chipsOnField3 = betInput;
                            break;
                        case 7:
                            mainPlayer->chipsOnField4 = betInput;
                            break;
                        case 8:
                            mainPlayer->chipsOnField9 = betInput;
                            break;
                        case 9:
                            mainPlayer->chipsOnField10 = betInput;
                            break;
                        case 10:
                            mainPlayer->chipsOnField11 = betInput;
                            break;
                        case 11:
                            mainPlayer->chipsOnField12 = betInput;
                            break;
                    }
                    printf("%sDo you want to make another bet? (1: Y, 2: N)%s\n", ANSI_GREEN, ANSI_RESET);
                    if (getIntInput(">", 1, 2) == 2)
                        break;
                }
                struct Node *currentComp = &(*computers->head);
                while (currentComp != NULL) {
                    int computerChoice = randomInRange(3, 11);
                    int chipsToPlace = randomInRange(1, currentComp->player->chips);
                    currentComp->player->chips -= chipsToPlace;
                    switch (computerChoice) {
                        case 3:
                            currentComp->player->chipsOnBigSix = chipsToPlace;
                            break;
                        case 4:
                            currentComp->player->chipsOnBigEight = chipsToPlace;
                            break;
                        case 5:
                            currentComp->player->chipsOnField2 = chipsToPlace;
                            break;
                        case 6:
                            currentComp->player->chipsOnField3 = chipsToPlace;
                            break;
                        case 7:
                            currentComp->player->chipsOnField4 = chipsToPlace;
                            break;
                        case 8:
                            currentComp->player->chipsOnField9 = chipsToPlace;
                            break;
                        case 9:
                            currentComp->player->chipsOnField10 = chipsToPlace;
                            break;
                        case 10:
                            currentComp->player->chipsOnField11 = chipsToPlace;
                            break;
                        case 11:
                            currentComp->player->chipsOnField12 = chipsToPlace;
                            break;
                    }
                    currentComp = currentComp->next;
                }
                firstRoll = randomInRange(1, 6);
                secondRoll = randomInRange(1, 6);
                total = firstRoll + secondRoll;
                printf("%s%s rolls the die...%s\n", ANSI_BLUE, (*shooter)->name, ANSI_RESET);
                printf("%sThe die hit the back table...%s\n", ANSI_GREEN, ANSI_RESET);
                printf("%s+---+ +---+%s\n", ANSI_ORANGE, ANSI_RESET);
                printf("%s+ %d + + %d +%s\n", ANSI_ORANGE, firstRoll, secondRoll, ANSI_RESET);
                printf("%s+---+ +---+%s\n", ANSI_ORANGE, ANSI_RESET);
                roll(total, &mainPlayer, &computers->head, false, point);
                if (total == point) {
                    printf("The point has been rolled.");
                    goto COME;
                }
            }
        }
    }
    return 0;
}