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
    // true if this square's value is redundant with another square's value
    bool inconsistent;
    bool hint;

    /*
    // candidate set will be a map with keys that are the numbers 1-9 and
    // values that are either "true" or "false". "true" if the user has
    // entered that number as a candidate and "false" if they haven't.

    std::map<int, bool> candidates; // candidate numbers
    */


public:
    // TODO implement accessor and mutator methods for value and candidates

    // Constructor
    // initialize each square as having no candidates entered
    Cell();

    // Accessors
    int get_value() const;
    bool is_fixed() const;
    bool is_inconsistent() const;
    bool is_hint() const;
    std::map<int, bool> get_candidates() const;

    // Specific getter for candidates map
    bool is_candidate(int candidate) const;

    // Mutators (Setters)
    void set_value(int value);
    void set_fixed(bool value);
    void set_inconsistent(bool value);
    void set_hint(bool value);
    void set_candidates(const std::map<int, bool>& candidates);

    // void set_candidate(int candidate, bool isCandidate);


};
