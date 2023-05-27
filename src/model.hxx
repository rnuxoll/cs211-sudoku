#pragma once

#include <ge211.hxx>
#include "board.hxx"

// Represents the state of the Reversi game.
class Model
{
public:

    // helpful aliases (inspired by Othello starter code)
    using Position = Board::Position;

    using Rectangle = Board::Rectangle;


    explicit Model(int size = 9);

    Rectangle all_positions() const;

    // Returns whether the game is finished. This is true when a correct
    // solution has been input
    bool game_over() const;

    // mutator methods
    void set_selected_cell(Position cell_index) const;


private:
    //
    // PRIVATE MEMBER VARIABLES
    //
    Board board_;

    Position selected_square_;

    bool is_game_over;

    // set game status to over, to be called if a correct solution is
    // implemented
    void set_game_over_();

    //
    void input_value_(Position square, int value);

    // adds a candidate number to the square
    void input_candidate_(Position square, int candidate);

};
