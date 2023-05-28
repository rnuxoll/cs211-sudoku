#pragma once

#include <ge211.hxx>

#include <iostream>
#include <array>
#include <set>
#include <vector>
#include "cell.hxx"
#include "position_set.hxx"

// citation: started with Othello board code and then modified it

const int BOARD_SIZE = 9; // sudoku board is 9x9
const int SQUARE_SIZE = 3; // sudoku square is 3x3


/// Represents the state of the board.
class Board
{
public:
    //
    // HELPFUL TYPE ALIASES
    //

    // Board positions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;


private:

    // the sudoku board here is an array of Cell objects
    // std::vector<std::vector<Cell>> board;
    std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE> board;

    // returns ture if the array has one of each integer from 1-9 (inclusive)
    // returns false otherwise
    bool is_legal_values(const std::array<int, BOARD_SIZE>& values) const;

    // given an array of up to 9 numbers, returns a set representing which
    // numbers are duplicates
    // if there are no duplicates, than returns an empty set
    std::set<int> get_duplicates(const std::array<Cell, BOARD_SIZE>& values)
    const;

    Dimensions dims_;




public:
    // constructor
    explicit Board(std::string board_string, Dimensions dims);

    Rectangle all_positions() const;

    // find which squares have redundant values and return them as a
    // Position_set
    Position_set find_contradictions() const;


    // helper function for find_contradictions()
    // finds all the cells that contradict the current value and returns
    // a Position_set with the indexes of the squares that do
    // returns an empty position_set if there are no contradicting squares
    // Position: cell_index the index of the cell whose contradictions
    // the function is supposed to find
    Position_set find_contradicting_squares(Position cell_index) const;

    // accessor methods
    int get_cell_value(int row, int col) const;

    // returns a live reference to a Cell in the board
    // modifying this reference modifies the cell!

    Cell get_cell (int row, int col) const;
    Cell& get_cell_reference(int row, int col);


    // gets the cell objects in the given row as values
    std::array<Cell, 9> get_row_values(int row);

    std::array<Cell, 9> get_col_values(int col);

    // maybe we can have it return index values instead of numbers
    // top-left square is 0, top-center is 1, top-right is 2, center-left is
    // 3, etc.
    std::array<std::array<Cell, 3>, 3> get_subgrid_values(int grid_index);


    std::map<int, bool> get_candidates(int row, int col) const;

    // mutator methods
    void set_cell_value(int row, int col, int value);
    void set_candidate(int row, int col, bool value);



    void mark_duplicates_in_row(int row);
    void mark_duplicates_in_col(int col);

    void mark_duplicates_in_square(int square);


    void mark_duplicates();

    // TODO
    // std::array<Cell, BOARD_SIZE> process

};


