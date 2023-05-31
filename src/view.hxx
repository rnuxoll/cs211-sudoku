#pragma once

#include "model.hxx"

class View
{
public:

    using Position = ge211::Posn<int>;
    using Dimensions = ge211::Dims<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    ge211::Dims<int> initial_window_dimensions() const;

    // convert between board coordinates and screen coordinates
    Position board_to_screen(Position board) const;
    Position screen_to_board(Position screen) const;

    Position cell_index_to_number_pos(Position index) const;

    Position mouse_posn_to_board(Position mouse_posn) const;

private:
    Model const& model_;

    Dimensions dims_;

    /// SPRITES

    // square sprites

    // TODO make all private variables end in an underscore
    ge211::Rectangle_sprite const white_square_sprite;
    ge211::Rectangle_sprite const shaded_square_sprite;
    ge211::Rectangle_sprite const selected_square_sprite;
    ge211::Rectangle_sprite const reveal_sprite;


    ge211::Circle_sprite const contradiction_dot_sprite;

    // grid line sprites
    ge211::Rectangle_sprite const horizontal_grid_line_sprite;
    ge211::Rectangle_sprite const vertical_grid_line_sprite;

    // number sprites
    ge211::Text_sprite one_sprite;
    ge211::Text_sprite two_sprite;
    ge211::Text_sprite three_sprite;
    ge211::Text_sprite four_sprite;
    ge211::Text_sprite five_sprite;
    ge211::Text_sprite six_sprite;
    ge211::Text_sprite seven_sprite;
    ge211::Text_sprite eight_sprite;
    ge211::Text_sprite nine_sprite;

    // hint number sprites
    ge211::Text_sprite one_hint_sprite;
    ge211::Text_sprite two_hint_sprite;
    ge211::Text_sprite three_hint_sprite;
    ge211::Text_sprite four_hint_sprite;
    ge211::Text_sprite five_hint_sprite;
    ge211::Text_sprite six_hint_sprite;
    ge211::Text_sprite seven_hint_sprite;
    ge211::Text_sprite eight_hint_sprite;
    ge211::Text_sprite nine_hint_sprite;

    ge211::Font sans72_{"sans.ttf", 72};



    // draws the sudoku board, with helper functions
    void draw_board(ge211::Sprite_set& set);

    // helper function for draw board which draws the numbers on the board
    // void draw_numbers(ge211::Sprite_set& set);

    // helper function for draw board which draws an individual cell
    void draw_cell(ge211::Sprite_set& set, Cell cell, bool selected);

    // draw a white square
    void draw_value_square(ge211::Sprite_set& set, Position box_coord);

    // draw a shaded square
    void draw_given_square(ge211::Sprite_set set, Position box_coord);

    // other helper functions for draw board
    void draw_one(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_two(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_three(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_four(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_five(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_six(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_seven(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_eight(ge211::Sprite_set& set, Position box_coord, bool is_hint);
    void draw_nine(ge211::Sprite_set& set, Position box_coord, bool is_hint);

    // helper function for draw_numbers which gives the
    ge211::Posn<int> get_center_of_square_in_screen(View::Position);


};
