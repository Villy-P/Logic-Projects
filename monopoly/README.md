# CPP-Monopoly

2080 lines of code written by me.
934 lines of data written by me.
141 lines of code not written by me.

## Sources

* [Stack Overflow](https://stackoverflow.com/)
* [Geeks for Geeks](https://www.geeksforgeeks.org/)
* [Tutorials Point](https://www.tutorialspoint.com/index.htm)
* [Techie Delight](https://www.techiedelight.com/)

## Languages used

* C++
* Header++

## Setup

First, you must activate ANSI escape sequences.

Open your command prompt by pressing `Windows+R` then type in `cmd`.

After that, enter this:

`REG ADD HKCU\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1`

The command prompt will respond with `The operation completed successfully`

Then, open the `main.exe` file in the folder `src`.

## C++

C++ is the language primarily used in this project.
It was made due to the original language C lacking classes and other features.
C is considered the "Mother of all programming languages," due to being used in the compilers of most languages.
C does not have many of the features that we take for granted today:

* Strings
* Classes
* For each
* Namespaces
* Try catch
* Dynamic arrays (vectors)
* Operator Overloading

One of the biggest things that C/C++ lack is garbage collection (C++ has *some* garbage collection, but C has none).
Garbage collection is where the program scans the stack to check for pointers to objects in the heap.
If an object is not in use, it deletes it and frees up the memory.
In C, you have to do that manually.

C++ is also notoriously complicated (mostly due to implementing pointers, which I'll go over later).
It is also known for being extremely fast.
C++ is about 10 times faster than Python.
The tradeoff, though, is that C++ takes very long to compile.
When you run a Python script, it almost automatically runs, however C++ can take a very long time to compile.
Another thing that C/C++ include is header files (.h/.hpp)
Header files are where we declare functions, and .cpp files are where we initialize them.
I'll go over that later.
C++ starts running from the `main.cpp` file in `src`, so we'll go there and trace through each file.

## #include

The first things we have in `main.cpp` is this:

``` cpp
#include "player.cpp"
#include "board.cpp"
#include "functions.hpp"
#include "card.cpp"
#include "cardManagment.cpp"

#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <windows.h>
```

The first batch of `#include` statements use quotes to get files in the current directory.
These are files that I have created.
The next batch use brackets, which means that the compiler searches for things in libraries (things that I have not made).
When we write `#include` statements, think of it as completely pasting whatever the contents of the file are in that location.

Next, we have two functions, but lets skip that and just go to the `main` function.

``` cpp
functions::clear();
```

This is the first line of our `main` function.
Here, we are calling the `clear()` function from the `functions` namespace.
The `functions` namespace is initialized in the `functions.cpp` file.
First however, lets go to the `functions.hpp` file, where `clear()` is declared.
To start, we have these two lines:

``` cpp
#ifndef SRC_FUNCTIONS_H_
#define SRC_FUNCTIONS_H_
```

And at the end we have this:

``` cpp
#endif
```

These are what are called `include guards`

When a `.hpp` file is included, it will first run the `#ifndef`.
That will check if `SRC_FUNCTIONS_H_` has been defined yet.
Since it has not been defined yet, it continue.
Then it `define`s `SRC_FUNCTIONS_H_`.
At the end of the file, it stops the `#ifndef`.
Then, when the `.hpp` file is included again, it will fail the `#ifndef` check, so the file will not run.
This is so that the functions within a header file will not be defined multiple times, but can be used multiple times.

Then we create a `namespace` that is called `functions`.
In order to access items of a namespace, you must use `::`.
For example, if we had a namespace called `ns` and a value called `vl`, you would do `ns::vl`.
Within our namespace, we declare `clear()`.
In our `functions.cpp` file, we `include` our header file, then later initialize `clear()` like this:

``` cpp
void functions::clear() {
    std::cout << "\033[2J" << std::endl;
}
```

## ANSI Escape Codes

`std::cout` and `std::endl` are part of the `<iostream>`, which is included above.
What we do here is first create an `std::cout`.
This starts writing to the console.
Then we use a `left shift` operator to print `\033[2J`.
Then we use `std::endl` to add a `\n` to the endl of the line.
This also flushes the console in order to stop weird behavior.
What we are printing is called an `ANSI Escape code`.
The `/033` initializes the code.
Then `[2J` clears the entire console screen.
While we are here, lets go over some other ANSI sequences.

In our `functions.hpp` file, we initialize lots of variables:

``` cpp
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
```

These are all ANSI Escape sequences.
The first one is used to stop all ANSI sequences.
The other ones start printing with color in the console.
In our `functions.cpp` file, we have these functions:

``` cpp
void functions::printlnRed(std::string str)     {std::cout << functions::ANSI_RED     << str << functions::ANSI_RESET << std::endl;}
void functions::printlnBlue(std::string str)    {std::cout << functions::ANSI_BLUE    << str << functions::ANSI_RESET << std::endl;}
void functions::printlnGreen(std::string str)   {std::cout << functions::ANSI_GREEN   << str << functions::ANSI_RESET << std::endl;}
void functions::printlnYellow(std::string str)  {std::cout << functions::ANSI_YELLOW  << str << functions::ANSI_RESET << std::endl;}
void functions::printlnMagenta(std::string str) {std::cout << functions::ANSI_MAGENTA << str << functions::ANSI_RESET << std::endl;}
void functions::printlnCyan(std::string str)    {std::cout << functions::ANSI_CYAN    << str << functions::ANSI_RESET << std::endl;}
```

Let's take the first functions, `printlnRed`.
It takes a string as an argument, which is what we will be printing.
Then, we start the printing process.
After that, we tell the console to start printing everything in red.
Then we print the string.
Then we stop printing in red and flush the console.

We will be using these functions a lot within this project.

Now back to our `main.cpp` file.

``` cpp
card_managment::CardManagment cardManager;
```

In our `cardManagment.hpp` file, we initialize a class called `CardManagment`.
Here we are creating a new variable called `cardManager` that is a class of `CardManagment`.
This adds the class to the stack.
You may be familiar with creating classes like this:

``` java
CardManagment cardManager = new CardManagment();
```

In C++, we *can* do this:

``` cpp
CardManagment* cardManager = new CardManagment();
```

Here we create an object on the heap.
In the stack, we have a pointer to the object on the heap, which is what the `*` is for.
Pointers are a huge hassle, so we will go over them later.

Next we call `cardManager.createCards()`:

``` cpp
std::ifstream cardData("cardData.txt");
card::Card card(true, "", {}, {});
if (cardData.is_open()) {
    while (cardData.good()) {
        std::string next;
        std::getline(cardData, next);
        card.isChance = functions::split(next, '=')[1] == "CHANCE";
        std::getline(cardData, next);
        card.description = functions::split(next, '=')[1];
        std::getline(cardData, next); // Get [FLAGS]
        std::getline(cardData, next); // Get first flag (OR PROPERTIES)
        while (next != "[PROPERTIES]") {
            card.flags.insert(next);
            std::getline(cardData, next);
        }
        std::getline(cardData, next);
        while (next != "-NEWCARD-") {
            std::vector<std::string> split = functions::split(next, '=');
            card.properties.insert({{split[0], split[1]}});
            getline(cardData, next);
        }
        card.isChance ? this->chanceCards.push_back(card) : this->chestCards.push_back(card);
        card = card::Card(true, "", {}, {});
    }
}
```

## Vectors

Since there are so many cards in Monopoly, I put all the data of the cards inside a `.txt` file.
Here, we are parsing this file to put the data into a `vector` of cards.
Think of a `vector` as an array that's size can be modified.

Take this array:

``` cpp
char[] str = {'a', 'b', 'c'};
```

Here we create an array of characters, otherwise known as a string.
This is what it looks like in memory:

``` txt
+---------------------+
|          a          |
+---------------------+
|          b          |
+---------------------+
|          c          |
+---------------------+
|       variable      |
+---------------------+
|                     |
+---------------------+
|                     |
+---------------------+
|                     |
+---------------------+
|                     |
+---------------------+
```

Now, lets say that `str` is a `vector`, and we add `d`.
Another variable is occupying the next space, so C++ has to manually move the memory:

``` txt
+---------------------+
|                     |
+---------------------+
|                     |
+---------------------+
|                     |
+---------------------+
|       variable      |
+---------------------+
|          a          |
+---------------------+
|          b          |
+---------------------+
|          c          |
+---------------------+
|          d          |
+---------------------+
```

Here, we start an `std::ifstream` called `cardData`.
We pass in the folder name to read there.

Then, we initialize an empty card to add to the vector.
The first `if` is to check if the file is valid.
Then we start a `while` loop that continues until the end of file.

Here is an example of a card:

``` txt
-NEWCARD-
TYPE=CHANCE
DESC=ADVANCE TO THE NEXT RAILROAD. If UNOWNED, you may buy it from the Bank. If OWNED, pay the owner twice the rent to which they are otherwise entitled. IF YOU PASS GO, COLLECT $200
[FLAGS]
MOVETONEXTRAILROAD
PAYDOUBLEIFOWNED
COLLECTGOCASH
[PROPERTIES]
-NEWCARD-
TYPE=CHANCE
DESC=SPEEDING FINE. PAY $15.
[FLAGS]
MONEYCHANGE
[PROPERTIES]
MONEYCHANGE=-15
```

First we say to create a new card.

``` cpp
std::string next;
std::getline(cardData, next);
```

The first line is to store the current line.
Then we use `getline` to get the first line.

After that, we check if the card is a chance card.
We do this by splitting the line that contains the TYPE.
We split it by the `=` sign, then get the last word found, which is either `CHEST` or `CHANCE`.
Here is our `split()` function:

``` cpp
std::vector<std::string> functions::split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}
```

Our arguments are a string, and a delimiter.
The `&` next to the `s` means that we will be passing in a *reference* to the string.
First we initialize a `stringstream`.
Then we create a variable that stores the current object.
After that we create a vector of all the split words.
Then, we push every item to that array, and return the vector.

Back to our functions, we then get the next line, and set the description to what we found.
Then, we loop over each flag and property and add it to their respective variables.

Flags will be used to identify what the card will do.
For example, in our card above, we known that, since `MONEYCHANGE` is in the flags, that the user's cash will be changed.

After that, we call `shuffleDecks()`:

``` cpp
std::default_random_engine rng = std::default_random_engine {};
std::shuffle(this->chanceCards.begin(), this->chanceCards.end(), rng);
std::shuffle(std::begin(this->chestCards), std::end(this->chestCards), rng);
```

This does, exactly what it says it does, shuffles both decks.
First it creates a `default_random_engine`.
Then it shuffles the deck by getting the beggining and end of the decks, as well as the `"random"` part.

Then we create a new `board` and call `createPlots`:

``` cpp
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
```

This is essentialy the exact same as the create cards file, so I won't go over it.

Since every plot is different, we need to use `FLAGS` and properties.

Then we create a new player.
The `true` within the parenthesis is a parameter, basically saying that this will be the main player.

Then we print the intro:

``` cpp
functions::printlnBlue("Welcome to Monopoly!");
functions::printlnGreen("What is your name?");
player.name = functions::readStringInput(">");
```

In order to get the name, we call this function:

``` cpp
std::string returnString;
std::cout << prompt;
std::getline(std::cin, returnString);
return returnString;
```

This essentialy gets the user input using `std::cin`.

The we clear the screen and ask the users how many computers they want to play against using these function:

``` cpp
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
```

First, we store the input as a string.
Then we call `tryParse`.
This will check if the user inputted an integer.
To do that it uses a `try-catch` block.
First it tries to do everything in the `try` block.
If any exeptions occur, it jumps to the `catch` block.
In the `try` block, we convert the output into an integer using `stoi`.
If it can't do that (say the input is `asdfoasj`), then we return `false`.
Otherwise, we return `true`.
Back to our `while` loop, we also check if the number is in the range specified.
Then, back in our `main` functions, we create all those computers.
You may notice that I use `unsigned char` instead of `int`.
Take this table:

| Name                         | Bits | Range                           |
|------------------------------|------|---------------------------------|
| char                         | 1    | -128 to 127 / 0 to 255          |
| unsigned char                | 1    | 0 to 255                        |
| signed char                  | 1    | -128 to 127                     |
| int / signed int             | 4    | -2147483648 to 2147483647       |
| unsigned int                 | 4    | 0 to 4294967295                 |
| short int / signed short int | 2    | -32768 to 32767                 |
| unsigned short int           | 2    | 0 to 65,535                     |
| long int / signed long int   | 8    | -2,147,483,648 to 2,147,483,647 |
| unsigned long int            | 8    | 0 to 4,294,967,295              |
| long long int                | 8    | -(2^63) to (2^63)-1             |
| unsigned long long int       | 8    | 0 to 18,446,744,073,709,551,615 |

Since I know that `i` will never be as large as an `int`, I can save 3 bytes.
In reality, it does not matter.

Then, we add that many computers to a vector.
We also set their names.
Then we clear the screen.

After that, we get the players identifier.
In order to do that, we call this function:

``` cpp
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
```

This is almost the same as the string functions, except that we check if the length of the string is one.

Then, since we don't want a computer to have the same identifier as the player, we remove that item from the array:

``` cpp
computerIdentifiers.erase(std::remove(computerIdentifiers.begin(), computerIdentifiers.end(), player.identifier), computerIdentifiers.end());
```

Here, we remove the item from the array by getting it's `beginning` and `end`.

We then clear the screen.
Then we get the color of the player:

``` cpp
std::string colorMenu() {
    std::cout << "Next, pick a color!" << std::endl;
    functions::printlnRed("1: Red");
    functions::printlnGreen("2: Green");
    functions::printlnYellow("3: Yellow");
    functions::printlnBlue("4: Blue");
    functions::printlnMagenta("5: Magenta");
    functions::printlnCyan("6: Cyan");
    switch (functions::readIntInput(">", 1, 6)) {
        case 1:     return functions::ANSI_RED;
        case 2:     return functions::ANSI_GREEN;
        case 3:     return functions::ANSI_YELLOW;
        case 4:     return functions::ANSI_BLUE;
        case 5:     return functions::ANSI_MAGENTA;
        case 6:     return functions::ANSI_CYAN;
    }
    return functions::ANSI_WHITE;
}
```

First, we print out all the options.
Then we run a `switch` on the player's input.
A `switch` is sort of like a switch.
Each `case` will check if the switched item is equal to that.
If it is, then we run whatever is there.

After that, we set the identifier color to what the player chose.

Then we list out the computers that the player will be going against.

After that, we have each player roll dice to determine who will go first:

``` cpp
std::vector<unsigned char> playerDice = board.rollDice();
unsigned char firstMoverCount = playerDice[0] + playerDice[1];
player::Player* mover = &player;
unsigned char moverIndex = 0;
for (unsigned char i = 0; i < computerNumber; i++) {
    std::vector<unsigned char> dice = board.rollDice();
    if (dice[0] + dice[1] > firstMoverCount) {
        firstMoverCount = dice[0] + dice[1];
        mover = &computers[i];
    }
}
functions::printlnGreen(mover->name + " will be moving first!");
functions::readStringInput("");
```

We first call this functions to get the player's die roll:

``` cpp
std::vector<unsigned char> board::Board::rollDice() {
    std::random_device random;
    std::mt19937 generate(random());
    std::uniform_int_distribution<> distr(1, 6);
    unsigned char die1 = distr(generate);
    unsigned char die2 = distr(generate);
    std::vector vect{die1, die2};
    return vect;
}
```

Here we generate a random device.
The `mt19937` is used to generate a seed for the random number generator.
Then we set the range from `1-6`.
Then we generate two random numbers between that range, add them to a vector, then return it.

Back to `main()`, we add the two items of the vector together to get the total die roll.
Since we know that the player has the highest die roll *so far*, we can set the current highest die roller to `player`.

And here is where we introduce `pointers`.

``` cpp
int num = 100;
```

Here we create a new number, and assign it to `100`.
When we create this variable, memory is allocated to store the variable:

``` c
// This is C
int* num = (int*) malloc(sizeof(int));
```

Here, we allocate 4 bytes of memory for an int known as `num`.
Here, we can see pointers at work.

``` c
int num = 100;
int* ptr = &num;

printf("%d\n", num);
printf("%p\n", ptr);
```

This will print `100` and then the memory location of num.
The `*` defines a pointer variable, and the `&` gets the memory location of the variable.

Here, we want to store the memory location of the player that will be moving first.
This is because if we *didn't*, we would just be storing a copy of the player.
If we ever want to change a member variable, say the players `cash`, it would assign it to the copy, not the original object.
In more *modern* languages, the language will do it for you.
Take Java.
You have your primitives (`'boolean''float', 'double', 'char', 'int', 'long'`).
You also have your non-primitives (`'String', any user created class, arrays`).
Primitives will always be passed by value.
Non-primitives will be passed by their memory location.
This is why in `Java`, you need to use `.equals` instead of `==`:
`==` will match the memory locations of the objects:

``` cpp
&obj1 == &obj2
```

Where `.equals` will match the content of the item.

Then we store the index of the mover's index (location of the computer moving).
Then we loop over each computer and check if the die roll is greater than the current largest roll.
After that, we print the name of the player moving first.
The empty `readStringInput()` is used as a stopping point, so that the player can specify when to continue.

Then we start an infinite loop.
First we call a functions that checks if there is only one player in the game.
If so we print that the player has won.
`exit(0)` stops the program completely.

Then, if the mover is the main player (i.e. you), then we call this function:

``` cpp
void player::Player::playerMenu(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers) {
    while (true) {
        functions::clear();
        functions::printlnCyan("1: Buy Houses");
        functions::printlnCyan("2: Buy Hotels");
        functions::printlnCyan("3: View Opponents");
        functions::printlnCyan("4: View Title Cards");
        functions::printlnCyan("5: Trade with computers");
        functions::printlnCyan("6: Mortgage property");
        functions::printlnCyan("7: Unmortgage property");
        functions::printlnCyan("8: Sell Houses");
        functions::printlnCyan("9: Sell Hotels");
        functions::printlnCyan("10: Roll/End Turn");
        switch (functions::readIntInput(">", 1, 10)) {
            case 1:
                this->buyHouse(board, mainPlayer, computers);
                break;
            case 2:
                this->buyHotel(board, mainPlayer, computers);
                break;
            case 3:
                this->displayOpponents(board, computers);
                break;
            case 4:
                this->displayTitleCards();
                break;
            case 5:
                this->trade(board, computers);
                break;
            case 6:
                this->mortgageProperty();
                break;
            case 7:
                this->unmortgageProperty();
                break;
            case 8:
                this->sellHouse(board);
                break;
            case 9:
                this->sellHotel();
                break;
            case 10:
                return;
        }
    }
}
```

You can think of this as an interlude menu.
Something that the player will see before and after they roll their die.

Let's go over each option:

## Buying a house

``` cpp
void player::Player::buyHouse(board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers) {
    if (!this->canBuyBuilding()) {
        if (this->isMainPlayer) {
            functions::printlnRed("You do not own any color sets");
            functions::readStringInput("");
        }
        return;
    }
    if (this->isMainPlayer) {
        for (int i = 0; i < this->ownedPlots.size(); i++) {
            std::cout << this->ownedPlots[i].stringProperties.at("COLORCODE") << std::to_string(i + 1) << ": " << this->ownedPlots[i].stringProperties.at("NAME");
            std::cout << " with " << std::to_string(this->ownedPlots[i].intProperties.at("HOUSES")) << " houses.";
            if (functions::setContains(this->ownedPlots[i].flags, "PROPERTYSQUARE"))
                std::cout << " A house there costs " << std::to_string(this->ownedPlots[i].intProperties.at("HOUSESCOST")) << functions::ANSI_RESET << std::endl;
        }
        functions::printlnRed("Enter 0 to exit");
        int input = functions::readIntInput(">", 0, this->ownedPlots.size());
        if (input == 0)
            return;
        if (functions::setContains(this->ownedPlots[input - 1].flags, "PROPERTYSQUARE")) {
            functions::printlnRed("That is not a property.");
            functions::readStringInput("");
            this->buyHouse(board, mainPlayer, computers);
        } else if (!this->ownsColorSet(this->ownedPlots[input - 1].stringProperties.at("COLORCODE"))) {
            functions::printlnRed("You do not own that color set.");
            functions::readStringInput("");
            this->buyHouse(board, mainPlayer, computers);
        } else if (functions::setContains(this->ownedPlots[input - 1].flags, "MORTGAGED")) {
            functions::printlnRed("That property is mortgaged.");
            functions::readStringInput("");
            this->buyHouse(board, mainPlayer, computers);
        } else if (!this->canBuyHouseOnPlot(this->ownedPlots[input - 1])) {
            functions::printlnRed("You must build houses equally.");
            functions::readStringInput("");
            this->buyHouse(board, mainPlayer, computers);
        } else if (this->ownedPlots[input - 1].intProperties.at("HOUSES") == 4) {
            functions::printlnRed("You already have 4 houses there. Build a hotel instead.");
            functions::readStringInput("");
            this->buyHouse(board, mainPlayer, computers);
        } else if (this->ownedPlots[input - 1].intProperties.at("HOTELS") == 1) {
            functions::printlnRed("You already have a hotel there.");
            functions::readStringInput("");
            this->buyHouse(board, mainPlayer, computers);
        } else if (this->cash < this->ownedPlots[input - 1].intProperties.at("HOUSESCOST")) {
            functions::printlnRed("You can't afford a house there.");
            functions::readStringInput("");
            this->buyHouse(board, mainPlayer, computers);
        }
        this->ownedPlots[input - 1].intProperties.at("HOUSES") += 1;
        this->reduceMoney(this->ownedPlots[input - 1].intProperties.at("HOUSESCOST"), board, mainPlayer, computers, false, mainPlayer);
    } else {
        for (plot::Plot& p : this->ownedPlots) {
            if (
                functions::setContains(p.flags, "PROPERTYSQUARE") &&
                !functions::setContains(p.flags, "MORTGAGED") &&
                this->ownsColorSet(p.stringProperties.at("COLORCODE")) &&
                this->canBuyHouseOnPlot(p) &&
                p.intProperties.at("HOUSES") != 4 &&
                p.intProperties.at("HOTELS") != 1 &&
                this->cash >= p.intProperties.at("HOUSESCOST")
            ) {
                functions::printlnBlue(this->name + " bought a house on " + p.stringProperties.at("NAME"));
                p.intProperties.at("HOUSES") += 1;
                this->reduceMoney(p.intProperties.at("HOUSESCOST"), board, mainPlayer, computers, false, mainPlayer);
                return;
            }
        }
    }
}
```

First, we call this function:

``` cpp
bool player::Player::canBuyBuilding() {
    for (plot::Plot& p : this->ownedPlots)
        if (this->ownsColorSet(p.stringProperties.at("COLORCODE")))
            return true;
    return false;
}
```

Here we loop over each of the players owned plots, and checks if they own the color set.
If they own at least one color set, we know they *can* buy a house there.
Each plot has a collection of string properties, such as their `name` and their `color`.
The `.at()` is used to get the value of the key that we pass in.
Here is the function to see if we own the color set:

``` cpp
bool player::Player::ownsColorSet(std::string color) {
    unsigned char matching = 0;
    for (plot::Plot& p : this->ownedPlots)
        if (p.stringProperties.at("COLORCODE") == color && functions::setContains(p.flags, "PROPERTYSQUARE"))
            matching++;
    return color == "BROWN" || color == "BLUE" ? matching == 2 : matching == 3;
}
```

First, we store the number of times a plot in the color set appears.
Then, we loop over each plot.
If the plots color code matches the color provided and the plot is a property, we add one to matching.

At the end, if the color is `brown` or `blue`, we return if the matching value was two.
This is because those color sets only have 2 streets on them.
Otherwise we return if the matching value was three.

Back to buying houses, if we do not own any color sets, then we tell the player that they cannot and return.

Then, we split the process of buying houses between computers and players.

If the player is the main player, we first print out each item in the owned plots.
Then we get the player input.
If it is 0 we exit.
Otherwise, we first check if the property selected is a property and not a railroad/utility.
If not we go to the start of the function.
Then, we check if the player owns the color set of the plot that they selected.
Then, if the property has the `MORTGAGED` flag, we stop.
Then we call this function:

``` cpp
bool player::Player::canBuyHouseOnPlot(plot::Plot& plot) {
    for (plot::Plot& p : this->ownedPlots) {
        if (
            !(p.stringProperties.at("COLORCODE") == plot.stringProperties.at("COLORCODE") && 
            p.intProperties.at("HOUSES") == plot.intProperties.at("HOUSES") ||
            p.intProperties.at("HOUSES") - 1 == plot.intProperties.at("HOUSES"))
        )
            return false;
    }
    return true;
}
```

Here we check if we are building houses equally.

If not, we stop.
We also stop if there is a hotel.
Then, if the property already has four houses we stop.
Finally, we stop if the player cannot afford the property.

If all these tests fail, we increase the number of houses on that property
Then we call the `reduceMoney()` method.

Then, if the player is a computer, we check if the opposite of all the above methods are true.
If so, we know we can buy a new house, so we do it.

No, lets go over the `reduceMoney()` method.
This method is used to reduce the amount of money a player has.

First we do this:

``` cpp
if (!this->inGame)
    return;
```

Here we check if the player is still in the game.
If not, we return.

Then, we check if the player cannot pay the amount.
If so, we then check if the player is the main player.
Then, we print that you cannot buy that property.
We then set up a `label` called `canMakeMoney`.
We can use the keyword `goto` to go to this label at any time.
We check if the player can gather the money by calling this function:

``` cpp
int player::Player::moneyCanMake() {
    int cashAvailable = this->cash;
    for (plot::Plot& p : this->ownedPlots) {
        cashAvailable += (p.intProperties.at("HOTELSCOST") / 2) * p.intProperties.at("HOTELS");
        cashAvailable += (p.intProperties.at("HOUSESCOST") / 2) * p.intProperties.at("HOUSES");
        cashAvailable += p.intProperties.at("UNMORTGAGEVALUE");
    }
    return cashAvailable;
}
```

First we store the amount of cash we have.
Then, we loop over each plot and calculate the total cash that can be gathered by selling buildings or mortgaging then.

This is used to check how much money the player *can* make.

Back to our `reduceMoney()` method,  if we can't make the money to pay off our debt, we then check if the player can trade their get out of jail free cards.

We get the money that the player wants to trade them for, then get a "pity" value for the computers.
If the computer is feeling generous enough, he will trade money for the cards.

If we can't make the money, we print some stuff then exit the program.

Now back a few steps, we now know the player can get the money.
So, we first start a sort of "while" loop with labels.
Then, we loop over all the plots the player has, and they can either sell buildings or mortgage property.
They do that until they have the cash, then we subtract the amount from the cash, then return.

If the player is a computer, we first check if he has get out of jail card, and see if the player will trade for it.
If he didn't have any cards then we start selling buildings and mortgaging properties.

If he goes bankrupt, we call this function:

``` cpp
void player::Player::computerBankruptcy(board::Board& board, std::vector<player::Player>& computers, player::Player& mainPlayer, bool doesOwe, player::Player& oweTo) {
    functions::printlnCyan(this->name + " has gone bankrupt.");
    this->inGame = false;
    if (doesOwe)
        for (plot::Plot& p : this->ownedPlots)
            oweTo.ownedPlots.push_back(p);
    else
        for (plot::Plot& p : this->ownedPlots)
            p.auction(board, mainPlayer, computers);
}
```

So here, we check if the computer owes someone.
If so we add all the owned properties to the person who the computer owes.
Otherwise, we auction off all the computers properties.

To auction, we call this function:

``` cpp
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
```

First off, we reset all the bids.
Then, we loop over each player and get their bid until all but one stops.
Then, we call this function to buy the function:

``` cpp
void player::Player::buyProperty(plot::Plot& nextPlot, board::Board& board, player::Player& mainPlayer, std::vector<player::Player>& computers) {
    if (functions::setContains(nextPlot.flags, "PROPERTYSQUARE"))
        nextPlot.displayTitleCard();
    else if (functions::setContains(nextPlot.flags, "RAILROAD"))
        nextPlot.displayRailroadCard();
    else
        nextPlot.displayUtilityCard();
    this->ownedPlots.push_back(nextPlot);
    nextPlot.flags.insert("OWNEDPLOT");
    this->cash -= nextPlot.intProperties.at("PRICE");
    nextPlot.stringProperties["OWNER"] = this->name;
    functions::readStringInput("");
}
```

First, we get which type of property type it is.
Then, we display the appropriate title card.
I won't go over these methods, but will go over two methods that are used to display strings:

``` cpp
std::string leftRightAdjust(std::string leftContent, std::string rightContent, int length) {
    return " " + leftContent + std::string(length - 2 - leftContent.length() - rightContent.length(), ' ') + rightContent + " ";
}
```

Here are printing two strings, seperated by spaces in order to print them at a certain length.
We also have this function:

``` cpp
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
```

Here, we center a string on a certain length.

Ok, so back a lot of steps, we return to the player menu.
Our next step is to buy hotels.
This is the exact same as buying houses, with a few changes, so I won't go over it.

After that, we have two functions that are used to display the properties of our opponents and ourselves.
These are quite self-explanitory, so I won't go over them.

After that, we have a function that deals with trades.

First, we get the computer the player wants to trade with.
Then, get the dimensions of the console using this function:

``` cpp
std::vector<int> functions::getConsoleDimensions() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    std::vector<int> dimensions;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    dimensions.push_back(info.srWindow.Right - info.srWindow.Left + 1);
    dimensions.push_back(info.srWindow.Bottom - info.srWindow.Top + 1);
    return dimensions;
}
```

If you were wondering why this project is windows only, this is why.

After that, we display the properies of each player.
Then, we get the amount of cash, properties, and get out of jail free cards that the player wants to trade.
Then, we check if the player is making a logical trade, and if so, we finalize the trade.

After that, we have functions to mortgage/unmortgage properties:

``` cpp
void player::Player::mortgageProperty() {
    functions::clear();
    for (int i = 0; i < this->ownedPlots.size(); i++) {
        std::cout << std::to_string(i + 1) << ": " << this->ownedPlots[i].stringProperties.at("COLORCODE") << this->ownedPlots[i].stringProperties.at("NAME") << " which is";
        std::cout << (functions::setContains(this->ownedPlots[i].flags, "MORTGAGED") ? " mortgaged." : " unmortgaged.") << " It has a mortgage value of $";
        std::cout << std::to_string(this->ownedPlots[i].intProperties.at("MORTGAGEVALUE")) << functions::ANSI_RESET << std::endl;
    }
    functions::printlnRed("Enter 0 to exit");
    int input = functions::readIntInput(">", 0, this->ownedPlots.size());
    if (input == 0)
        return;
    if (functions::setContains(this->ownedPlots[input - 1].flags, "MORTGAGED")) {
        functions::printlnRed("That property is already mortgaged. Try unmortgaging it.");
        functions::readStringInput("");
        this->mortgageProperty();
    }
    this->ownedPlots[input - 1].flags.insert("MORTGAGED");
    this->cash += this->ownedPlots[input - 1].intProperties.at("MORTGAGEVALUE");
    functions::printlnGreen("You have mortgaged that property.");
    functions::readStringInput("");
}

void player::Player::unmortgageProperty() {
    functions::clear();
    for (int i = 0; i < this->ownedPlots.size(); i++) {
        std::cout << std::to_string(i + 1) << ": " << this->ownedPlots[i].stringProperties.at("COLORCODE") << this->ownedPlots[i].stringProperties.at("NAME") << " which is";
        std::cout << (functions::setContains(this->ownedPlots[i].flags, "MORTGAGED") ? " mortgaged." : " unmortgaged.") << " It has a mortgage value of $";
        std::cout << std::to_string(this->ownedPlots[i].intProperties.at("UNMORTGAGEVALUE")) << functions::ANSI_RESET << std::endl;
    }
    functions::printlnRed("Enter 0 to exit");
    int input = functions::readIntInput(">", 0, this->ownedPlots.size());
    if (input == 0)
        return;
    if (functions::setContains(this->ownedPlots[input - 1].flags, "UNMORTGAGE")) {
        functions::printlnRed("That property is already unmortgaged.");
        functions::readStringInput("");
        this->unmortgageProperty();
    } else if (this->cash < this->ownedPlots[input - 1].intProperties.at("UNMORTGAGEVALUE")) {
        functions::printlnRed("You can't afford that!.");
        functions::readStringInput("");
        this->unmortgageProperty();
    }
    this->ownedPlots[input - 1].flags.erase("MORTGAGED");
    this->cash -= this->ownedPlots[input - 1].intProperties.at("UNMORTGAGEVALUE");
    functions::printlnGreen("You have unmortgaged that property.");
    functions::readStringInput("");
}
```

Here, we get the player's input on which property they want to mortgage/unmortgage.

Then, if we are mortgaging a property, we get the money associated with it.
Otherwise, we pay the money needed.

Then, we have two functions that sell buildings, which is the opposite of the previous functions to buy buildings.

Later we call the `movePlayer()` function  which prints out the players die roll and move the player.
All those functions are in the `player.cpp` file.

Thanks!
