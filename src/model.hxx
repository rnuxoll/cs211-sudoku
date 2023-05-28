#pragma once

#include <ge211.hxx>
#include "board.hxx"

// Represents the state of the Reversi game.
class Model
{
public:

    // helpful aliases (inspired by Othello starter code)
    //using Position = Board::Position;
    using Position = ge211::Posn<int>;

    using Rectangle = Board::Rectangle;

    Model();

    Model(std::string board_string);

    Rectangle all_positions() const;

    // Returns whether the game is finished. This is true when a correct
    // solution has been input
    bool game_over() const;

    // mutator methods
    void set_selected_cell(Position cell_index);

    // accessor methods
    Board get_board() const;
    Position get_selected_cell() const;


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
