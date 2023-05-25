//
// Created by Ravi Nuxoll on 5/24/23.
//

#ifndef GAME_SQUARE_HXX
#define GAME_SQUARE_HXX

#endif //GAME_SQUARE_HXX

#include <array>
#include <map>

class Cell{

private:
    int value;
    bool fixed;

    // candidate set will be a map with keys that are the numbers 1-9 and
    // values that are either "true" or "false". "true" if the user has
    // entered that number as a candidate and "false" if they haven't.

    std::map<int, bool> candidates; // candidate numbers


public:
    // TODO implement accessor and mutator methods for value and candidates

    // Constructor
    // initialize each square as having no candidates entered
    Cell() : value(0), fixed(false){
        for (int i = 1; i <= 9; i++){
            candidates[i] = false;
        }
    }

};