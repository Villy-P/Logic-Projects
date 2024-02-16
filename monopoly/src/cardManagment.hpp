#ifndef CARD_MANAGMENT_HPP
#define CARD_MANAGMENT_HPP

#include <deque>

#include "card.hpp"
#include "board.hpp"

namespace card_managment {
    class CardManagment {
        public: 
            std::deque<card::Card> chanceCards;
            std::deque<card::Card> chestCards;

            void shuffleDecks();
            void drawChanceCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player);
            void drawChestCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player);
            void createCards();

            void redeemCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void changeMoney(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void moveToNextRailroad(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void goBack(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void payEach(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void advanceTo(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void getOutOfJailFreeCard(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void repairHouses(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void repairHotels(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void advanceToNearestUtility(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
            void collectFromEach(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers, player::Player& player, card::Card& card);
    };
}

#endif