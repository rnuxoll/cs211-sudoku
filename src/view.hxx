#pragma once

#include "model.hxx"

class View
{
public:

    using Position = ge211::Posn<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;

    /// SPRITES

    // square sprites
    ge211::Rectangle_sprite const white_square_sprite;
    ge211::Rectangle_sprite const shaded_square_sprite;
    ge211::Rectangle_sprite const contradiction_square_sprite;

    // grid line sprites
    ge211::Rectangle_sprite const horizontal_grid_line_sprite;
    ge211::Rectangle_sprite const vertical_grid_line_sprite;

    // number sprites
    ge211::Text_sprite const one_sprite;
    ge211::Text_sprite const two_sprite;
    ge211::Text_sprite const three_sprite;
    ge211::Text_sprite const four_sprite;
    ge211::Text_sprite const five_sprite;
    ge211::Text_sprite const six_sprite;
    ge211::Text_sprite const seven_sprite;
    ge211::Text_sprite const eight_sprite;
    ge211::Text_sprite const nine_sprite;

    // convert between board coordinates and screen coordinates
    Position board_to_screen(Position board) const;
    Position screen_to_board(Position screen) const;

    // draws the sudoku board, with helper functions
    void draw_board(ge211::Sprite_set& set);

    // helper function for draw board which draws the numbers on the board
    void draw_numbers(ge211::Sprite_set& set);

    // other helper functions for draw board
    void draw_one(ge211::Sprite_set& set, Position box_coord);
    void draw_two(ge211::Sprite_set& set, Position box_coord);
    void draw_three(ge211::Sprite_set& set, Position box_coord);
    void draw_four(ge211::Sprite_set& set, Position box_coord);
    void draw_five(ge211::Sprite_set& set, Position box_coord);
    void draw_six(ge211::Sprite_set& set, Position box_coord);
    void draw_seven(ge211::Sprite_set& set, Position box_coord);
    void draw_eight(ge211::Sprite_set& set, Position box_coord);
    void draw_nine(ge211::Sprite_set& set, Position box_coord);

    // helper function for draw_numbers which gives the
    ge211::Posn<int> get_center_of_square_in_screen(View::Position);

    // other helper functions for draw_numbers

};
