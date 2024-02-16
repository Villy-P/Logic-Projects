#ifndef SRC_PLOT_H_
#define SRC_PLOT_H_

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

#include "player.cpp"
#include "board.hpp"

namespace plot {
    class Plot {
        public:
            std::unordered_set<std::string> flags;
            std::unordered_map<std::string, std::string> stringProperties;
            std::unordered_map<std::string, int> intProperties;

            Plot(
                std::unordered_set<std::string> flags,
                std::unordered_map<std::string, std::string> stringProperties,
                std::unordered_map<std::string, int> intProperties
            );

            void displayTitleCard();
            void displayUtilityCard();
            void displayRailroadCard();
            std::string getRentWithHouseString(unsigned char number, std::string name, unsigned char titleCardLength);
            void auction(board::Board& board, player::Player& player, std::vector<player::Player>& computers);
            bool playersStillBidding(std::vector<player::Player>& players, player::Player& mainPlayer);
    };
}

#endif
