#pragma once

#include "plot.hpp"

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <limits>

std::string center(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int pad = w - s.size();
    for (int i = 0; i < pad / 2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();
    if (pad > 0 && pad % 2 != 0)
        ss << " ";
    return ss.str();
}

std::string leftRightAdjust(std::string leftContent, std::string rightContent, unsigned char length) {
    return " " + leftContent + std::string(length - 2 - leftContent.length() - rightContent.length(), ' ') + rightContent + " ";
}

plot::Plot::Plot(std::unordered_set<std::string> flags, std::unordered_map<std::string, std::string> stringProperties, std::unordered_map<std::string, int> intProperties) {
    this->flags = flags;
    this->stringProperties = stringProperties;
    this->intProperties = intProperties;
}

void plot::Plot::displayTitleCard() {
    unsigned char titleCardLength = 29;
    std::string repeatedDash = std::string(titleCardLength, '-');
    std::string repeatedSpace = std::string(titleCardLength, ' ');
    std::cout << this->stringProperties.at("COLORCODE") << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << center("TITLE DEED", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center(this->stringProperties.at("NAME"), titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << leftRightAdjust("Rent", "$" + std::to_string(this->intProperties.at("RENT")), titleCardLength) << "|" << std::endl;
    std::cout << this->stringProperties.at("COLORCODE") << "|" << leftRightAdjust("Rent with color set", "$" + std::to_string(this->intProperties.at("RENTWITHCOLORSET")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("Rent with 1 home", "$" + std::to_string(this->intProperties.at("RENTWITHONEHOUSE")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("Rent with 2 houses", "$" + std::to_string(this->intProperties.at("RENTWITHTWOHOUSES")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("Rent with 3 houses", "$" + std::to_string(this->intProperties.at("RENTWITHTHREEHOUSES")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("Rent with 4 houses", "$" + std::to_string(this->intProperties.at("RENTWITHFOURHOUSES")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("Rent with hotel", "$" + std::to_string(this->intProperties.at("RENTWITHHOTEL")), titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << leftRightAdjust("Houses cost", "$" + std::to_string(this->intProperties.at("HOUSESCOST")) + " each", titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("Hotels cost", "$" + std::to_string(this->intProperties.at("HOTELSCOST")) + " each", titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("", "(plus 4 houses)", titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << center("MORTGAGE", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("VALUE $" + std::to_string(this->intProperties.at("MORTGAGEVALUE")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << repeatedSpace << "|" << std::endl;
    std::cout << "|" << center("TO UNMORTGAGE,", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("PAY $" + std::to_string(this->intProperties.at("UNMORTGAGEVALUE")), titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << "\033[0m" << std::endl;
}

void plot::Plot::displayUtilityCard() {
    unsigned char titleCardLength = 28;
    std::string repeatedDash = std::string(titleCardLength, '-');
    std::string repeatedSpace = std::string(titleCardLength, ' ');
    std::cout << this->stringProperties.at("COLORCODE") << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << center(this->stringProperties.at("NAME"), titleCardLength) << "|" << std::endl;
    std::cout << "|" << repeatedSpace << "|" << std::endl;
    std::cout << "|" << center("If one Utility is owned,", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("rent is 4 times amount", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("shown on dice.", titleCardLength) << "|" << std::endl;
    std::cout << "|" << repeatedSpace << "|" << std::endl;
    std::cout << "|" << center("If both Utilities are owned,", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("rent is 10 times amount", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("shown on dice.", titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << center("MORTGAGE", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("VALUE $" + std::to_string(this->intProperties.at("MORTGAGEVALUE")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << repeatedSpace << "|" << std::endl;
    std::cout << "|" << center("TO UNMORTGAGE,", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("PAY $" + std::to_string(this->intProperties.at("UNMORTGAGEVALUE")), titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << "\033[0m" << std::endl;
}

void plot::Plot::displayRailroadCard() {
    unsigned char titleCardLength = 34;
    std::string repeatedDash = std::string(titleCardLength, '-');
    std::string repeatedSpace = std::string(titleCardLength, ' ');
    std::cout << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << center(this->stringProperties.at("NAME"), titleCardLength) << "|" << std::endl;
    std::cout << "|" << repeatedSpace << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("RENT", "$25", titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("If 2 Railroads are owned", "$50", titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("If 3 Railroads are owned", "$100", titleCardLength) << "|" << std::endl;
    std::cout << "|" << leftRightAdjust("If 4 Railroads are owned", "$200", titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << std::endl;
    std::cout << "|" << center("MORTGAGE", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("VALUE $" + std::to_string(this->intProperties.at("MORTGAGEVALUE")), titleCardLength) << "|" << std::endl;
    std::cout << "|" << repeatedSpace << "|" << std::endl;
    std::cout << "|" << center("TO UNMORTGAGE,", titleCardLength) << "|" << std::endl;
    std::cout << "|" << center("PAY $" + std::to_string(this->intProperties.at("UNMORTGAGEVALUE")), titleCardLength) << "|" << std::endl;
    std::cout << "+" << repeatedDash << "+" << std::endl;
}

std::string plot::Plot::getRentWithHouseString(unsigned char number, std::string name, unsigned char titleCardLength) {
    return " WITH " + std::to_string(number) + " HOUSE" + std::string(titleCardLength - 15 - std::to_string(this->intProperties.at(name)).length(), ' ') + "$" + std::to_string(this->intProperties.at(name)) + " ";
}

void plot::Plot::auction(board::Board& board, player::Player& player, std::vector<player::Player>& computers) {
    player.bid = 0;
    player.isBidding = true;
    for (player::Player& c : computers) {
        c.bid = 0;
        c.isBidding = true;
    }
    std::cout << "Bidding has started on the property " << this->stringProperties.at("COLORCODE") << this->stringProperties.at("NAME") << functions::ANSI_RESET << std::endl;
    player::Player* highestBidder = &player;
    while (this->playersStillBidding(computers, player)) {
        functions::printlnBlue("The bid has passed to you. You can either (1) enter a new bid, or (2) stop bidding.");
        int input = functions::readIntInput(">", 1, 2);
        if (input == 1) {
            functions::printlnMagenta("The current bid is $" + std::to_string(highestBidder->bid) + ". You have $" + std::to_string(player.cash));
            functions::printlnMagenta("You may go over your cash, however you mush raise the money to pay and may end up going bankrupt.");
            input = functions::readIntInput(">", highestBidder->bid + 1, std::numeric_limits<int>::max());
            highestBidder = &player;
            player.bid = input;
        } else {
            functions::printlnRed("You have stopped bidding.");
            player.isBidding = false;
        }
        functions::readStringInput(">");
        for (player::Player& p : computers) {
            if (p.isBidding && p.inGame) {
                if (p.cash <= highestBidder->bid || highestBidder->bid > this->intProperties.at("PRICE") + 30 || p.cash <= this->intProperties.at("PRICE") + 30) {
                    functions::printlnRed(p.name + " has stopped bidding.");
                    p.isBidding = false;
                } else {
                    p.bid = highestBidder->bid + 30;
                    highestBidder = &p;
                    functions::printlnRed(p.name + " has raised the bid to $" + std::to_string(p.bid));
                }
            }
        }
    }
    functions::printlnGreen("The auction has ended!");
    functions::printlnBlue(highestBidder->name + " is the highest bidder at $" + std::to_string(highestBidder->bid));
    highestBidder->reduceMoney(highestBidder->bid, board, player, computers, false, player);
    highestBidder->buyProperty(*this, board, player, computers);
}

bool plot::Plot::playersStillBidding(std::vector<player::Player>& players, player::Player& mainPlayer) {
    int playersStillBidding = 0;
    if (mainPlayer.isBidding)
        playersStillBidding++;
    for (player::Player& p : players)
        if (p.isBidding)
            playersStillBidding++;
    return playersStillBidding > 1;
}