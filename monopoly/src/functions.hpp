#ifndef SRC_FUNCTIONS_H_
#define SRC_FUNCTIONS_H_

#include <vector>
#include <string>
#include <unordered_set>

#include "card.hpp"

namespace functions {
    std::string ANSI_RESET     = "\033[0m";
    std::string ANSI_RED       = "\033[31m";
    std::string ANSI_GREEN     = "\033[32m";
    std::string ANSI_YELLOW    = "\033[33m";
    std::string ANSI_BLUE      = "\033[34m";
    std::string ANSI_MAGENTA   = "\033[35m";
    std::string ANSI_CYAN      = "\033[36m";
    std::string ANSI_WHITE     = "\033[37m";
    std::string ANSI_BROWN     = "\033[38;5;52m";
    std::string ANSI_DARK_CYAN = "\033[38;5;23m";
    std::string ANSI_ORANGE    = "\033[38;5;202m";
    std::string ANSI_PURPLE    = "\033[38;5;127m";

    std::vector<std::string> split(const std::string &s, char delim);
    std::vector<int> getConsoleDimensions();
    std::vector<card::Card> shuffle(std::vector<card::Card> vec);
    bool setContains(std::unordered_set<std::string>& set, std::string str);
    bool tryParse(std::string &input, int &output);
    int readIntInput(std::string prompt, int min, int max);
    std::string center(const std::string s, const int w);
    std::string readStringInput(std::string prompt);
    std::string readCharInput(std::string prompt);
    void clear();
    void printlnRed(std::string str);
    void printlnBlue(std::string str);
    void printlnGreen(std::string str);
    void printlnYellow(std::string str);
    void printlnMagenta(std::string str);
    void printlnCyan(std::string str);
}

#endif
