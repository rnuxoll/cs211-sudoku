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
    // bool is_legal_values(const std::array<int, BOARD_SIZE>& values) const;

    // given an array of up to 9 numbers, returns a set representing which
    // numbers are duplicates
    // if there are no duplicates, than returns an empty set
    std::set<int> get_duplicates(const std::array<Cell, BOARD_SIZE> values)
    const;

    Dimensions dims_;




public:
    // constructor
    explicit Board(std::string board_string, Dimensions dims);

    Rectangle all_positions() const;


    // accessor methods
    // returns a live reference to a Cell in the board
    // modifying this reference modifies the cell!

    Cell get_cell (int col, int row) const;
    Cell& get_cell_reference(int col, int row);


    // gets the cell objects in the given row as values
    std::array<Cell, BOARD_SIZE> get_row_cell_values(int row);

    std::array<Cell, BOARD_SIZE> get_col_cell_values(int col);

    // maybe we can have it return index_ values instead of numbers
    // top-left square is 0, top-center is 1, top-right is 2, center-left is
    // 3, etc.

    // idea: for bonus fun, make this depend on the square root of BOARD_SIZE
    // and therefore see if you can extend it to any integer-square, not just 9

    // the grid indexes are defined as follows
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // std::array<std::array<Cell, 3>, 3> get_square_cell_values(int square_index);
    std::array<Cell, BOARD_SIZE> get_square_cell_values(int square_index);

    // mutator methods

    void mark_duplicates_in_row(int row);
    void mark_duplicates_in_col(int col);

    void mark_duplicates_in_square(int square_index);


    void mark_duplicates();

};


