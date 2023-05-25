#pragma once

#include <ge211.hxx>

#include <iostream>
#include <array>
#include <set>
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
    using Position = ge211::Posn<int>;

private:

    // the sudoku board here is an array of Cell objects
    std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE> board;

    // returns ture if the array has one of each integer from 1-9 (inclusive)
    // returns false otherwise
    bool is_legal_values(const std::array<int, BOARD_SIZE>& values) const;

    // given an array of up to 9 numbers, returns a set representing which
    // numbers are duplicates
    // if there are no duplicates, than returns an empty set
    std::set<int> get_duplicates(const std::array<int, BOARD_SIZE>& values)
    const;



public:
    // constructor
    Board();

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
    std::map<int, bool> get_candidates(int row, int col) const;

    // mutator methods
    void set_cell_value(int row, int col, int value);
    void set_candidate(int row, int col, bool value);

    // TODO
    // std::array<Cell, BOARD_SIZE> process

};


