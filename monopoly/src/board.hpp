#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_

#include <vector>
#include <string>

namespace player{class Player;}
namespace plot{class Plot;}

namespace board {
    class Board {
        public:
            std::vector<player::Player> players;
            std::vector<plot::Plot> plots;

            std::vector<unsigned char> rollDice();
            std::string getStringProperty(int index, std::string propertyName);
            plot::Plot& getPlot(int index);
            int getIntProperty(int index, std::string propertyName);
            void createPlots();
    };
}

#endif
