#ifndef BOARD_CPP
#define BOARD_CPP

#include "board.hpp"
#include "plot.cpp"
#include "functions.cpp"

#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <iostream>

std::vector<unsigned char> board::Board::rollDice() {
    std::random_device random;
    std::mt19937 generate(random());
    std::uniform_int_distribution<> distr(1, 6);
    unsigned char die1 = distr(generate);
    unsigned char die2 = distr(generate);
    std::vector vect{die1, die2};
    return vect;
}

plot::Plot& board::Board::getPlot(int index) {
    return this->plots[index >= (this->plots.size()) ? index - this->plots.size() : index];
}

void board::Board::createPlots() {
    std::ifstream plotData("plotData.txt");
    plot::Plot plot({}, {}, {});
    if (plotData.is_open()) {
        while (plotData.good()) {
            std::string next;
            std::getline(plotData, next); // Get [FLAGS]
            std::getline(plotData, next); // Get first flag (OR STRING_PROPERTIES)
            while (next != "[STRING_PROPERTIES]") {
                plot.flags.insert(next);
                std::getline(plotData, next);
            }
            std::getline(plotData, next);
            while (next != "[INT_PROPERTIES]") {
                std::vector<std::string> split = functions::split(next, '=');
                if (split[0] == "COLORCODE") {
                    if (split[1] == "WHITE")
                        split[1] = functions::ANSI_WHITE;
                    else if (split[1] == "BROWN")
                        split[1] = functions::ANSI_BROWN;
                    else if (split[1] == "DARK_CYAN")
                        split[1] = functions::ANSI_DARK_CYAN;
                    else if (split[1] == "CYAN")
                        split[1] = functions::ANSI_CYAN;
                    else if (split[1] == "ORANGE")
                        split[1] = functions::ANSI_ORANGE;
                    else if (split[1] == "MAGENTA")
                        split[1] = functions::ANSI_MAGENTA;
                    else if (split[1] == "YELLOW")
                        split[1] = functions::ANSI_YELLOW;
                    else if (split[1] == "RED")
                        split[1] = functions::ANSI_RED;
                    else if (split[1] == "BLUE")
                        split[1] = functions::ANSI_BLUE;
                    else if (split[1] == "GREEN")
                        split[1] = functions::ANSI_GREEN;
                }
                plot.stringProperties.insert({{split[0], split[1]}});
                std::getline(plotData, next);
            }
            std::getline(plotData, next);
            while (next != "-NEWPLOT-") {
                std::vector<std::string> split = functions::split(next, '=');
                plot.intProperties.insert({{split[0], stoi(split[1])}});
                getline(plotData, next);
            }
            this->plots.push_back(plot);
            plot = plot::Plot{{}, {}, {}};
        }
    } else {
        functions::printlnRed("FATAL ERROR. CANNOT FIND OR READ FILE NAMED PLOTDATA.TXT");
        functions::printlnRed("PLEASE CHECK THAT THE FILE EXISTS WITHIN THE SAME DIRECTORY AS MAIN.EXE AND CHECK FILE PERMISSIONS");
        functions::readStringInput("PRESS ENTER TO ABORT.");
        exit(0);
    }
}

std::string board::Board::getStringProperty(int index, std::string propertyName) {
    return this->plots.at(index >= (this->plots.size()) ? index - this->plots.size() : index).stringProperties.at(propertyName);
}

int board::Board::getIntProperty(int index, std::string propertyName) {
    return this->plots.at(index >= (this->plots.size()) ? index - this->plots.size() : index).intProperties.at(propertyName);
}

#endif
