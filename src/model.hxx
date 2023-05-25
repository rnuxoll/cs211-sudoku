#pragma once

#include <ge211.hxx>
#include "board.hxx"
#include "cell.hxx"

// Represents the state of the Reversi game.
class Model
{
public:

    // helpful aliases
    using Position

    // Returns a rectangle containing all the positions of the board.
    // This can be used to iterate over the positions.
    Rectangle all_positions() const;

    // Returns whether the game is finished. This is true when a correct
    // solution has been input
    bool is_game_over() const;


    Cell operator[](Position) const;



#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

private:
    //
    // PRIVATE MEMBER VARIABLES
    //
    Board board_;

    Position selected_square_;

    // set game status to over, to be called if a correct solution is
    // implemented
    void set_game_over_();

    //
    void input_value(Position square, int value);

    /// adds a candidate number to the square
    void input_candidate(Position square, int candidate);

};
