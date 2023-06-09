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

    Model(): Model(get_random_board()) {};


    // "b" for beginner game
    // "n" for normal game
    // "e" for expert game
    void start_new_game(char difficulty);

    Model(const std::pair<Board, Board>& board_solution);

    // Returns whether the game is finished. This is true when a correct
    // solution has been input
    void check_game_over();

    // accessor method for the game_over variable
    bool is_game_over() const;

    bool is_new_game() const;

    void set_menu_screen();

    // mutator methods
    void set_selected_cell(Position cell_index);

    void move_select_up();
    void move_select_down();
    void move_select_left();
    void move_select_right();

    // accessor methods
    Board get_board() const;

    Board& get_board_reference();

    Position get_selected_cell() const;

    void print_board() const;

    // process_numerical_input function will take an int
    // and will update the model only if that square is not a
    // fixed_ or not a hint_
    void process_numerical_input(int n);

    // attempt to clear the value_ from the selected cell
    // passes only if the cell is not a hint_ and not a given
    void attempt_clear_selected_cell();

    void reveal_answer();

    static std::pair<Board, Board> get_random_board();

    static std::pair<Board, Board> get_random_beginner_game();
    static std::pair<Board, Board> get_random_normal_game();
    static std::pair<Board, Board> get_random_expert_game();


private:
    //
    // PRIVATE MEMBER VARIABLES
    //
    Board board_;

    Board solution_;

    Position selected_cell_index_;

    bool new_game_;
    bool game_over_;

    bool is_in_bounds(Position cell_index) const;


    // set game status to over, to be called if a correct solution is
    // implemented
    // void set_game_over_();

    // adds a candidate number to the square
    // void input_candidate_(Position square, int candidate);

};
