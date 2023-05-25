#pragma once

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>
#include "cell.hxx"

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
    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;


    // TODO can probably delete this
    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    // Defined and documented below.
    class reference;

private:

    // the sudoku board here is an array of Cell objects
    std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE> board;

    Dimensions dims_;


public:

    // constructor
    Board();

    // accessor methods
    int get_cell_value(int row, int col) const;
    std::map<int, bool> get_candidates(int row, int col) const;



    // mutator methods
    void set_cell_value(int row, int col, int value);

    //

private:
    //
    // PRIVATE HELPER FUNCTION MEMBERS
    //

    Player get_(Position where) const;
    void set_(Position where, Player who);
    void bounds_check_(Position where) const;

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif
};


//
// FREE FUNCTIONS FOR WORKING WITH THE CLASS
//

/// Inequality for boards.
bool
operator!=(Board const&, Board const&);

/// Board printing, suitable for debugging.
std::ostream&
operator<<(std::ostream&, Board const&);


//
// HELPER CLASSES
//

/// Class returned by `operator[](Position)` that simulates
/// an assignable reference to a `Posn<int>`. This is what allows
/// you to write
///
///     board[pos] = player;
///
/// to place `player` at `pos`.
///
/// The definition of the class follows this definition of the
/// `Board` class.
class Board::reference
{
    Board& board_;
    Position pos_;

public:
    /// Assigns the value of `that` to the object of `this`.
    reference& operator=(reference const&) noexcept;

    /// Assigns to the object of the reference.
    reference& operator=(Player) noexcept;

    /// Returns the value of the reference.
    operator Player() const noexcept;

private:
    friend class Board;

    reference(Board&, Position) noexcept;
};


/// Class returned by `at_set(Position_set)` that allows assigning
/// one player to all the positions in the given `Position_set`.
class Board::multi_reference
{
    Board& board_;
    Position_set pos_set_;

public:
    /// Assigns the given player to all the positions of this
    /// multi-reference, which are all the positions in the set that
    /// was given to `Board::at_set(Position_set)`. Thus, you can
    /// mass-assign a player to a set of positions like so:
    ///
    ///     // Sets three positions to dark:
    ///     Position_set positions{{0, 0}, {1, 1}, {2, 2}};
    ///     board.at_set(positions) = Player::dark;
    ///
    multi_reference& operator=(Player) noexcept;

private:
    friend class Board;

    multi_reference(Board&, Position_set) noexcept;
};

