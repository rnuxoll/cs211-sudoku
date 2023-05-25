#pragma once

#include <ge211.hxx>
#include "board.hxx"
#include "cell.hxx"

// Represents the state of the Reversi game.
class Model
{
public:
    /// Model dimensions will use `int` coordinates
    using Dimensions = Board::Dimensions;

    /// Model positions will use `int` coordinates
    using Position = Board::Position;

    /// Model rectangles will use `int` coordinates, as board rectangles do.
    using Rectangle = Board::Rectangle;

    /// Constructs a model with `size` as both its width and height.
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if `size` is less than 2
    ///    or greater than 10.
    explicit Model(int size = 10);

    /// Constructs a model with the given width and height.
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if either dimension is less
    ///    than 2 or greater than 8.
    Model(int width, int height);

    /// Returns a rectangle containing all the positions of the board.
    /// This can be used to iterate over the positions.
    Rectangle all_positions() const;

    /// Returns whether the game is finished. This is true when a correct
    /// solution has been input
    bool is_game_over() const;



    /// Returns the Cell at the given position
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if the position is out of
    ///    bounds.
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

    //
    // PRIVATE HELPER FUNCTIONS
    //

    //
    Position_set find_contradictions_(Position start, Dimensions dir) const;

    /// Sets the game status to over
    /// to be called if a correct solution has been input
    void set_game_over_();

    /// modifies the inputs in the board with a user value
    void input_value(Position square, int value);

    /// adds a candidate number to the square
    void input_candidate(Position square, int candidate);

};
