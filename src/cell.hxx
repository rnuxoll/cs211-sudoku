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

    int value_;
    bool fixed_;
    // true if this square's value_ is redundant with another square's value_
    bool row_inconsistent_;
    bool col_inconsistent_;
    bool square_inconsistent_;
    bool hint_;
    Position index_;

    /*
    // candidate set will be a map with keys that are the numbers 1-9 and
    // values that are either "true" or "false". "true" if the user has
    // entered that number as a candidate and "false" if they haven't.

    std::map<int, bool> candidates; // candidate numbers
    */


public:
    Cell() : value_(0), fixed_(false),
            row_inconsistent_(false),
            col_inconsistent_(false),
            square_inconsistent_(false),
            hint_(false), index_{0, 0} {}

    // Constructor
    // initialize each square as having no candidates entered
    Cell(int value, Position ind);
    int get_value() const;
    void set_value(int value);
    // set inconsistent sets row inconsistent if code is r
    // set inconsistent sets col inconsistent if code is c
    // set inconsistent sets square inconsistent if code is s
    void set_inconsistent(bool value, char code);
    void set_hint(bool value);
    // accessor methods
    bool is_fixed() const;
    bool is_inconsistent() const;
    bool is_hint() const;
    // void set_candidate(int candidate, bool isCandidate);

    Position get_index();


};
