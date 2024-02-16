#pragma once

#include "functions.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include  <random>
#include  <iterator>
#include <algorithm>
#include <windows.h>

std::vector<card::Card> functions::shuffle(std::vector<card::Card> vec) {
    static auto rng = std::default_random_engine {};
    std::shuffle(std::begin(vec), std::end(vec), rng);
    return vec;

}

void functions::clear() {
    std::cout << "\033[2J" << std::endl;
}

std::string functions::center(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int pad = w - s.size();                  // count excess room to pad
    for(int i=0; i<pad/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str(); // format with padding
    if(pad>0 && pad%2!=0)                    // if pad odd #, add 1 more space
        ss << " ";
    return ss.str();
}

std::vector<int> functions::getConsoleDimensions() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    std::vector<int> dimensions;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    dimensions.push_back(info.srWindow.Right - info.srWindow.Left + 1);
    dimensions.push_back(info.srWindow.Bottom - info.srWindow.Top + 1);
    return dimensions;
}

void functions::printlnRed(std::string str)     {std::cout << functions::ANSI_RED     << str << functions::ANSI_RESET << std::endl;}
void functions::printlnBlue(std::string str)    {std::cout << functions::ANSI_BLUE    << str << functions::ANSI_RESET << std::endl;}
void functions::printlnGreen(std::string str)   {std::cout << functions::ANSI_GREEN   << str << functions::ANSI_RESET << std::endl;}
void functions::printlnYellow(std::string str)  {std::cout << functions::ANSI_YELLOW  << str << functions::ANSI_RESET << std::endl;}
void functions::printlnMagenta(std::string str) {std::cout << functions::ANSI_MAGENTA << str << functions::ANSI_RESET << std::endl;}
void functions::printlnCyan(std::string str)    {std::cout << functions::ANSI_CYAN    << str << functions::ANSI_RESET << std::endl;}

bool functions::setContains(std::unordered_set<std::string>& set, std::string str) {
    return set.find(str) != set.end();
}

std::vector<std::string> functions::split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

std::string functions::readStringInput(std::string prompt) {
    std::string returnString;
    std::cout << prompt;
    std::getline(std::cin, returnString);
    return returnString;
}

std::string functions::readCharInput(std::string prompt) {
    std::string returnString;
    std::cout << prompt;
    std::getline(std::cin, returnString);
    while (returnString.length() != 1) {
        std::cout << "Enter a character>";
        std::getline(std::cin, returnString);
    }
    return returnString;
}

bool functions::tryParse(std::string &input, int &output) {
    try {
        output = stoi(input);
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}

int functions::readIntInput(std::string prompt, int min, int max) {
    std::string input;
    std::cout << prompt;
    int x;
    std::getline(std::cin, input);
    while (!tryParse(input, x) || x < min || x > max) {
        std::cout << "Enter a number between " << min << " & " << max << ">";
        std::getline(std::cin, input);
    }
    return x;
}
