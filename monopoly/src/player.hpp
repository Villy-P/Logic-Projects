#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "board.hpp"
#include "plot.hpp"
#include "cardManagment.hpp"

#include <string>
#include <vector>

namespace player {
    class Player {
        public:
            std::string name;
            std::string identifier;
            int cash = 1500;
            int plotPosition = 0;
            int bid = 0;
            bool isMainPlayer;
            bool isBidding = true;
            bool inGame = true;
            bool inJail = false;
            unsigned char turnsInJail = 0;
            unsigned char getOutOfJailFreeCards = 0;
            unsigned char doubles = 0;
            std::vector<plot::Plot> ownedPlots;

            Player(bool isMainPlayer);

            int moneyCanMake();
            int moneyInTrade(int moneyToGive, std::vector<plot::Plot*>& plots, int cardsToGive);
            void movePlayer(board::Board& board, Player& mainPlayer, std::vector<Player>& computers, card_managment::CardManagment& cardManager);
            bool ownsPlot(plot::Plot& plot);
            bool ownsColorSet(std::string color);
            bool canBuyBuilding();
            bool canBuyHouseOnPlot(plot::Plot& plot);
            bool canBuyHotelOnPlot(plot::Plot& plot);
            bool doesPlayerOwnFourHouses();
            unsigned char ownedRailroads();
            unsigned char ownedUtilities();
            void computerBankruptcy(board::Board& board, std::vector<Player>& computers, Player& mainPlayer, bool doesOwe, Player& oweTo);
            void reduceMoney(int amount, board::Board& board, Player& mainPlayer, std::vector<player::Player>& computers, bool doesOwe, Player& oweTo);
            void payRent(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, std::vector<unsigned char>& dieRoll);
            void payRentOnProperty(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& whoOwns);
            void payRentOnRailroad(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& whoOwns, bool payTwice);
            void payRentOnUtility(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& whoOwns, std::vector<unsigned char> dieRoll, unsigned char timesAmount);
            void buyProperty(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers);
            void buyPropertyAsMainPlayer(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers);
            void buyPropertyAsComputer(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers);
            void buyPropertySegment(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers);
            void landOnSquare(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, card_managment::CardManagment& cardManager, std::vector<unsigned char> dieRoll);
            void whileInJail(board::Board& board, Player& mainPlayer, std::vector<Player>& computers, card_managment::CardManagment& cardManager);
            void getOutOfJail(board::Board& board, Player& mainPlayer, std::vector<Player>& computers, card_managment::CardManagment& cardManager);
            void playerMenu(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers);
            void buyHouse(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers);
            void buyHotel(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers);
            void displayOpponents(board::Board& board, std::vector<player::Player>& computers);
            void displayTitleCards();
            void mortgageProperty();
            void unmortgageProperty();
            void sellHouse(board::Board& board);
            void sellHotel();
            void trade(board::Board& board, std::vector<player::Player>& computers);
    };
}

#endif
