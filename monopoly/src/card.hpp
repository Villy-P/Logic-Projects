#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace card {
    class Card {
        public:

            bool isChance;
            std::string description;
            std::unordered_set<std::string> flags;
            std::unordered_map<std::string, std::string> properties;

            Card(bool isChance, std::string description, std::unordered_set<std::string> flags, std::unordered_map<std::string, std::string> properties);
    };
}

#endif