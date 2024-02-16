#ifndef CARD_CPP
#define CARD_CPP

#include "card.hpp"

#include "functions.cpp"

#include <string>
#include <unordered_set>
#include <unordered_map>

card::Card::Card(bool isChance, std::string description, std::unordered_set<std::string> flags, std::unordered_map<std::string, std::string> properties) {
    this->isChance = isChance;
    this->description = description;
    this->flags = flags;
    this->properties = properties;
}

#endif