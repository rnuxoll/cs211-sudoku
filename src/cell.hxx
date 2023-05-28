//
// Created by Ravi Nuxoll on 5/24/23.
//

#ifndef GAME_SQUARE_HXX
#define GAME_SQUARE_HXX

#endif //GAME_SQUARE_HXX

#include <array>
#include <map>
#include <ge211.hxx>

class Cell{

private:

    using Position = ge211::Posn<int>;

    int value;
    bool fixed;
    // true if this square's value is redundant with another square's value
    bool inconsistent;
    bool hint;
    Position index;

    /*
    // candidate set will be a map with keys that are the numbers 1-9 and
    // values that are either "true" or "false". "true" if the user has
    // entered that number as a candidate and "false" if they haven't.

    std::map<int, bool> candidates; // candidate numbers
    */


public:
    // TODO implement accessor and mutator methods for value and candidates

    Cell() : value(0), fixed(false), inconsistent(false), hint(false),
    index{0, 0} {}

    // Constructor
    // initialize each square as having no candidates entered
    Cell(int value, Position ind);
    int get_value() const;
    void set_value(int value);
    void set_fixed(bool value);
    void set_inconsistent();

    // accessor methods
    bool is_fixed() const;
    bool is_inconsistent() const;
    bool is_hint() const;
    // void set_candidate(int candidate, bool isCandidate);

    Position get_index();


};
