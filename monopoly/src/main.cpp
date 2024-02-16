#include "player.cpp"
#include "board.cpp"
#include "functions.hpp"
#include "card.cpp"
#include "cardManagment.cpp"

#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <windows.h>

std::string colorMenu() {
    std::cout << "Next, pick a color!" << std::endl;
    functions::printlnRed("1: Red");
    functions::printlnGreen("2: Green");
    functions::printlnYellow("3: Yellow");
    functions::printlnBlue("4: Blue");
    functions::printlnMagenta("5: Magenta");
    functions::printlnCyan("6: Cyan");
    switch (functions::readIntInput(">", 1, 6)) {
        case 1:     return functions::ANSI_RED;
        case 2:     return functions::ANSI_GREEN;
        case 3:     return functions::ANSI_YELLOW;
        case 4:     return functions::ANSI_BLUE;
        case 5:     return functions::ANSI_MAGENTA;
        case 6:     return functions::ANSI_CYAN;
    }
    return functions::ANSI_WHITE;
}

unsigned char getPlayersInGame(player::Player& mainPlayer, std::vector<player::Player>& computers) {
    unsigned char playersStillInGame = 0;
    if (mainPlayer.inGame)
        playersStillInGame++;
    for (player::Player& player : computers)
        if (player.inGame)
            playersStillInGame++;
    return playersStillInGame;
}

int main(void) {
    functions::clear();
    card_managment::CardManagment cardManager;
    cardManager.createCards();
    cardManager.shuffleDecks();
    board::Board board;
    board.createPlots();
    player::Player player(true);
    functions::printlnBlue("Welcome to Monopoly!");
    functions::printlnGreen("What is your name?");
    player.name = functions::readStringInput(">");
    functions::clear();
    functions::printlnMagenta("How many computers do you want to play against? (1-7)");
    unsigned char computerNumber = functions::readIntInput(">", 1, 7);
    std::vector<player::Player> computers;
    std::vector<std::string> computerIdentifiers{"!", "@", "#", "$", "%", "^", "&", "*"};
    for (unsigned char i = 0; i < computerNumber; i++) {
        computers.push_back(player::Player(false));
        computers[i].name = "Computer #" + std::to_string(i);
    }
    functions::clear();
    functions::printlnCyan("First, pick an identifier! (Must be single character)");
    player.identifier = functions::readCharInput(">");
    computerIdentifiers.erase(std::remove(computerIdentifiers.begin(), computerIdentifiers.end(), player.identifier), computerIdentifiers.end());
    functions::clear();
    std::string identifierColor = colorMenu();
    player.identifier = identifierColor + player.identifier + functions::ANSI_RESET;
    functions::clear();
    functions::printlnBlue("You will be identified as " + player.identifier);
    functions::printlnGreen("Here are your opponents:");
    for (unsigned char i = 0; i < computerNumber; i++) {
        computers[i].identifier = computerIdentifiers[i];
        functions::printlnRed(computers[i].name + " as " + computers[i].identifier);
    }
    std::vector<unsigned char> playerDice = board.rollDice();
    unsigned char firstMoverCount = playerDice[0] + playerDice[1];
    player::Player* mover = &player;
    unsigned char moverIndex = 0;
    for (unsigned char i = 0; i < computerNumber; i++) {
        std::vector<unsigned char> dice = board.rollDice();
        if (dice[0] + dice[1] > firstMoverCount) {
            firstMoverCount = dice[0] + dice[1];
            mover = &computers[i];
        }
    }
    functions::printlnGreen(mover->name + " will be moving first!");
    functions::readStringInput("");
    while (true) {
        if (getPlayersInGame(player, computers) == 1) {
            functions::printlnBlue("You have won the game!");
            functions::printlnBlue("Press ENTER to abort");
            functions::readStringInput("");
            exit(0);
        }
        if (mover->isMainPlayer) {
            mover->playerMenu(board, player, computers);
        } else {
            mover->buyHouse(board, player, computers);
            mover->buyHotel(board, player, computers);
        }
        mover->movePlayer(board, player, computers, cardManager);
        if (mover->isMainPlayer)
            mover->playerMenu(board, player, computers);
        if (mover->isMainPlayer)
            mover = &computers[moverIndex];
        else if (mover->name == "Computer #" + std::to_string(computers.size() - 1)) {
            mover = &player;
            moverIndex = 0;
        }
        else
            mover = &computers[++moverIndex];
    }
}