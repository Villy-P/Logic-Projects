#ifndef CARD_MANAGMENT_CPP
#define CARD_MANAGMENT_CPP

#include "cardManagment.hpp"
#include "functions.cpp"
#include "player.cpp"

#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

void card_managment::CardManagment::shuffleDecks() {
    std::default_random_engine rng = std::default_random_engine {};
    std::shuffle(this->chanceCards.begin(), this->chanceCards.end(), rng);
    std::shuffle(std::begin(this->chestCards), std::end(this->chestCards), rng);
}

void card_managment::CardManagment::createCards() {
    std::ifstream cardData("cardData.txt");
    card::Card card(true, "", {}, {});
    if (cardData.is_open()) {
        while (cardData.good()) {
            std::string next;
            std::getline(cardData, next);
            card.isChance = functions::split(next, '=')[1] == "CHANCE";
            std::getline(cardData, next);
            card.description = functions::split(next, '=')[1];
            std::getline(cardData, next); // Get [FLAGS]
            std::getline(cardData, next); // Get first flag (OR PROPERTIES)
            while (next != "[PROPERTIES]") {
                card.flags.insert(next);
                std::getline(cardData, next);
            }
            std::getline(cardData, next);
            while (next != "-NEWCARD-") {
                std::vector<std::string> split = functions::split(next, '=');
                card.properties.insert({{split[0], split[1]}});
                getline(cardData, next);
            }
            card.isChance ? this->chanceCards.push_back(card) : this->chestCards.push_back(card);
                card = card::Card(true, "", {}, {});
        }
    }
}

void card_managment::CardManagment::drawChanceCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player) {
    card::Card card = this->chanceCards[0];
    if (functions::setContains(card.flags, "WITHPLAYER")) {
        this->chanceCards.pop_front();
        this->chanceCards.push_back(card);
        this->drawChanceCard(board, mainPlayer, computers, player);
    }
    std::vector<std::string> displaySentence = functions::split(card.description, ' ');
    unsigned char lengthOfEach = displaySentence.size() / 5;
    unsigned char extraLetters = displaySentence.size() % 5;
    std::cout << "+---------------------------------------------+" << std::endl;
    std::cout << "|                    OOOOOO                   |" << std::endl;
    std::cout << "|                    O    O                   |" << std::endl;
    std::cout << "|                      OOOO                   |" << std::endl;
    std::cout << "|                      O                      |" << std::endl;
    std::cout << "|                      .                      |" << std::endl;
    std::cout << "+---------------------------------------------+" << std::endl;
    functions::readStringInput("");
    std::cout << "+----------------------------------------------+" << std::endl;
    for (unsigned char start = 0, end = lengthOfEach; start < displaySentence.size(); start = end, end = start + lengthOfEach) {
        if (extraLetters) {
            end++;
            extraLetters--;
        }
        std::string str = "";
        for (unsigned char i = start; i < end; i++)
            str +=  displaySentence[i] + " ";
        str.pop_back();
        std::cout << "|" << functions::center(str, 46) << "|" << std::endl;
    }
    std::cout << "+----------------------------------------------+" << std::endl;
    this->chanceCards.pop_front();
    this->chanceCards.push_back(card);
    this->redeemCard(board, mainPlayer, computers, player, card);
}

void card_managment::CardManagment::drawChestCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player) {
    card::Card card = this->chestCards[0];
    if (functions::setContains(card.flags, "WITHPLAYER")) {
        this->chanceCards.pop_front();
        this->chanceCards.push_back(card);
        this->drawChanceCard(board, mainPlayer, computers, player);
    }
    std::vector<std::string> displaySentence = functions::split(card.description, ' ');
    unsigned char lengthOfEach = displaySentence.size() / 5;
    unsigned char extraLetters = displaySentence.size() % 5;
    std::cout << "+---------------------------------------------+" << std::endl;
    std::cout << "|                      +------+-+             |" << std::endl;
    std::cout << "|                     /      / /              |" << std::endl;
    std::cout << "|                    .^__/\\_._.               |" << std::endl;
    std::cout << "|                  +--------+V+               |" << std::endl;
    std::cout << "|                  +________+.+               |" << std::endl;
    std::cout << "+---------------------------------------------+" << std::endl;
    functions::readStringInput("");
    std::cout << "+----------------------------------------------+" << std::endl;
    for (unsigned char start = 0, end = lengthOfEach; start < displaySentence.size(); start = end, end = start + lengthOfEach) {
        if (extraLetters) {
            end++;
            extraLetters--;
        }
        std::string str = "";
        for (unsigned char i = start; i < end; i++)
            str +=  displaySentence[i] + " ";
        str.pop_back();
        std::cout << "|" << functions::center(str, 46) << "|" << std::endl;
    }
    std::cout << "+----------------------------------------------+" << std::endl;
    this->chestCards.pop_front();
    this->chestCards.push_back(card);
    this->redeemCard(board, mainPlayer, computers, player, card);
}

void card_managment::CardManagment::redeemCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    if (functions::setContains(card.flags, "MONEYCHANGE"))
        this->changeMoney(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "MOVETONEXTRAILROAD"))
        this->moveToNextRailroad(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "GOBACK"))
        this->goBack(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "PAYEACH"))
        this->payEach(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "ADVANCETO"))
        this->advanceTo(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "GETOUTOFJAILFREECARD"))
        this->getOutOfJailFreeCard(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "REPAIRHOUSES"))
        this->repairHouses(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "REPAIRHOTELS"))
        this->repairHotels(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "ADVANCETONEARESTUTILITY"))
        this->advanceToNearestUtility(board, mainPlayer, computers, player, card);
    if (functions::setContains(card.flags, "COLLECTFROMEACH"))
        this->collectFromEach(board, mainPlayer, computers, player, card);
}

void card_managment::CardManagment::changeMoney(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    if (std::stoi(card.properties.at("MONEYCHANGE")) > 0)
        player.cash += std::stoi(card.properties.at("MONEYCHANGE"));
    else
        player.reduceMoney(std::stoi(card.properties.at("MONEYCHANGE")), board, mainPlayer, computers, false, player);
}

void card_managment::CardManagment::moveToNextRailroad(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    if (player.plotPosition < 5 || player.plotPosition > 35) {
        if (player.plotPosition < 40) {
            std::cout << player.name << " passes by GO. +$200" << std::endl;
            player.cash += 200;
        }
        player.plotPosition = 5;
    }
    else if (player.plotPosition < 15)
        player.plotPosition = 15;
    else if (player.plotPosition < 25)
        player.plotPosition = 25;
    else if (player.plotPosition < 35)
        player.plotPosition = 35;
    player::Player whoOwns(false);
    if (mainPlayer.ownsPlot(board.getPlot(player.plotPosition)))
        whoOwns = mainPlayer;
    for (player::Player p : computers)
        if (p.ownsPlot(board.getPlot(player.plotPosition)))
            whoOwns = p;
    if (functions::setContains(board.getPlot(player.plotPosition).flags, "OWNEDPLOT") && board.getPlot(player.plotPosition).stringProperties.at("OWNER") != player.name)
        player.payRentOnRailroad(board.getPlot(player.plotPosition), board, mainPlayer, computers, whoOwns, true);
    else
        player.buyPropertySegment(board.getPlot(player.plotPosition), board, mainPlayer, computers);
}

void card_managment::CardManagment::goBack(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    player.plotPosition -= std::stoi(card.properties.at("GOBACKAMOUNT"));
    player.landOnSquare(board.getPlot(player.plotPosition), board, mainPlayer, computers, *this, {0, 0});
}

void card_managment::CardManagment::payEach(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    if (player.isMainPlayer) {
        for (player::Player& p : computers) {
            if (p.inGame) {
                player.reduceMoney(std::stoi(card.properties.at("PAYEACHAMOUNT")), board, mainPlayer, computers, true, p);
                p.cash += std::stoi(card.properties.at("PAYEACHAMOUNT"));
            }
        }
    } else {
        player.reduceMoney(std::stoi(card.properties.at("PAYEACHAMOUNT")), board, mainPlayer, computers, true, mainPlayer);
        mainPlayer.cash += std::stoi(card.properties.at("PAYEACHAMOUNT"));
        for (player::Player& p : computers) {
            if (p.inGame && p.name != player.name) {
                player.reduceMoney(std::stoi(card.properties.at("PAYEACHAMOUNT")), board, mainPlayer, computers, true, p);
                p.cash += std::stoi(card.properties.at("PAYEACHAMOUNT"));
            }
        }
    }
}

void card_managment::CardManagment::advanceTo(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    if (player.plotPosition > std::stoi(card.properties.at("ADVANCEINDEX")) && functions::setContains(card.flags, "GOTOJAIL")) {
        std::cout << player.name << " passes by GO. +$200" << std::endl;
        player.cash += 200;
    }
    player.plotPosition = std::stoi(card.properties.at("ADVANCEINDEX"));
    player.landOnSquare(board.getPlot(player.plotPosition), board, mainPlayer, computers, *this, {0, 0});
    if (functions::setContains(card.flags, "GOTOJAIL"))
        player.inJail = true;
}

void card_managment::CardManagment::getOutOfJailFreeCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    player.getOutOfJailFreeCards++;
}

void card_managment::CardManagment::repairHouses(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    int amount = 0;
    for (plot::Plot& p : player.ownedPlots)
        amount += std::stoi(card.properties.at("REPAIRHOUSESCOST")) * p.intProperties.at("HOUSES");
    player.reduceMoney(amount, board, mainPlayer, computers, false, player);
}

void card_managment::CardManagment::repairHotels(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    int amount = 0;
    for (plot::Plot& p : player.ownedPlots)
        amount += std::stoi(card.properties.at("REPAIRHOTELSCOST")) * p.intProperties.at("HOTELS");
    player.reduceMoney(amount, board, mainPlayer, computers, false, player);
}

void card_managment::CardManagment::advanceToNearestUtility(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    if (player.plotPosition < 12 || player.plotPosition > 28) {
        if (player.plotPosition < 40) {
            std::cout << player.name << " passes by GO. +$200" << std::endl;
            player.cash += 200;
        }
        player.plotPosition = 12;
    } else {
        player.plotPosition = 28;
    }
    player::Player whoOwns(false);
    if (mainPlayer.ownsPlot(board.getPlot(player.plotPosition)))
        whoOwns = mainPlayer;
    for (player::Player p : computers)
        if (p.ownsPlot(board.getPlot(player.plotPosition)))
            whoOwns = p;
    if (functions::setContains(board.getPlot(player.plotPosition).flags, "OWNEDPLOT") && board.getPlot(player.plotPosition).stringProperties.at("OWNER") != player.name)
        player.payRentOnUtility(board.getPlot(player.plotPosition), board, mainPlayer, computers, whoOwns, board.rollDice(), 10);
    else
        player.buyPropertySegment(board.getPlot(player.plotPosition), board, mainPlayer, computers);
}

void card_managment::CardManagment::collectFromEach(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card) {
    if (player.isMainPlayer) {
        for (player::Player& p : computers) {
            if (p.inGame) {
                p.reduceMoney(std::stoi(card.properties.at("COLLECTFROMEACHAMOUNT")), board, mainPlayer, computers, true, p);
                player.cash += std::stoi(card.properties.at("COLLECTFROMEACHAMOUNT"));
            }
        }
    } else {
        mainPlayer.reduceMoney(std::stoi(card.properties.at("COLLECTFROMEACHAMOUNT")), board, mainPlayer, computers, true, mainPlayer);
        player.cash += std::stoi(card.properties.at("COLLECTFROMEACHAMOUNT"));
        for (player::Player& p : computers) {
            if (p.inGame && p.name != player.name) {
                p.reduceMoney(std::stoi(card.properties.at("COLLECTFROMEACHAMOUNT")), board, mainPlayer, computers, true, p);
                player.cash += std::stoi(card.properties.at("COLLECTFROMEACHAMOUNT"));
            }
        }
    }
}

#endif