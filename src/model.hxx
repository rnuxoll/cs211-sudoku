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

    Model(std::string board_string, std::string solution_string);

    Rectangle all_positions() const;

    // Returns whether the game is finished. This is true when a correct
    // solution has been input
    bool game_over() const;

    // mutator methods
    void set_selected_cell(Position cell_index);

    void move_select_up();
    void move_select_down();
    void move_select_left();
    void move_select_right();

    // accessor methods
    Board get_board() const;
    Position get_selected_cell() const;



    void print_board() const;

    // process_numerical_input function will take an int
    // and will update the model only if that square is not a
    // fixed or not a hint
    void process_numerical_input(int n);


private:
    //
    // PRIVATE MEMBER VARIABLES
    //
    Board board_;

    Board solution_;

    Position selected_cell_index_;

    bool is_game_over_;

    bool is_in_bounds(Position cell_index) const;


    // set game status to over, to be called if a correct solution is
    // implemented
    void set_game_over_();

    //
    void input_value_(Position square, int value);

    // adds a candidate number to the square
    void input_candidate_(Position square, int candidate);

};
