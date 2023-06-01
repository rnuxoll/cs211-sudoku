#pragma once

#include "model.hxx"

const int TEXT_Z = 5;

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

    /// SPRITES

    // square sprites

    // TODO make all private variables end in an underscore
    ge211::Rectangle_sprite const white_square_sprite_;
    ge211::Rectangle_sprite const shaded_square_sprite_;
    ge211::Rectangle_sprite const selected_square_sprite_;
    ge211::Rectangle_sprite const reveal_sprite_;

    ge211::Circle_sprite const contradiction_dot_sprite_;

    // grid line sprites
    ge211::Rectangle_sprite const horizontal_grid_line_sprite_;
    ge211::Rectangle_sprite const vertical_grid_line_sprite_;
    ge211::Rectangle_sprite const thick_horizontal_grid_line_sprite_;
    ge211::Rectangle_sprite const thick_vertical_grid_line_sprite_;

    // number sprites
    ge211::Text_sprite one_sprite_;
    ge211::Text_sprite two_sprite_;
    ge211::Text_sprite three_sprite_;
    ge211::Text_sprite four_sprite_;
    ge211::Text_sprite five_sprite_;
    ge211::Text_sprite six_sprite_;
    ge211::Text_sprite seven_sprite_;
    ge211::Text_sprite eight_sprite_;
    ge211::Text_sprite nine_sprite_;

    // hint_ number sprites
    ge211::Text_sprite one_hint_sprite_;
    ge211::Text_sprite two_hint_sprite_;
    ge211::Text_sprite three_hint_sprite_;
    ge211::Text_sprite four_hint_sprite_;
    ge211::Text_sprite five_hint_sprite_;
    ge211::Text_sprite six_hint_sprite_;
    ge211::Text_sprite seven_hint_sprite_;
    ge211::Text_sprite eight_hint_sprite_;
    ge211::Text_sprite nine_hint_sprite_;

    ge211::Font sans72_{"sans.ttf", 72};
    // ge211::Font sans36_{"sans.ttf", 36};

    ge211::Text_sprite you_win_sprite_;
    ge211::Text_sprite for_new_game_sprite_;
    ge211::Text_sprite press_sprite_;
    ge211::Text_sprite b_beginner_sprite_;
    ge211::Text_sprite n_normal_sprite_;
    ge211::Text_sprite e_expert_sprite_;

    // draws the sudoku board, with helper functions
    void draw_board(ge211::Sprite_set& set);

    void draw_new_game(ge211::Sprite_set& set);

    void draw_congratulations(ge211::Sprite_set& set);


    void draw_you_win(ge211::Sprite_set& set, Position start_cell_index);

    void draw_for_new_game(ge211::Sprite_set& set,
                           Position start_cell_index);

    void draw_press(ge211::Sprite_set& set, Position start_cell_index);

    void draw_difficulty_levels(ge211::Sprite_set& set, Position
    start_cell_index);

    // helper function for draw board which draws the numbers on the board
    // void draw_numbers(ge211::Sprite_set& set);

    // helper function for draw board which draws an individual cell
    void draw_cell(ge211::Sprite_set& set, Cell cell, bool selected);

    // other helper functions for draw board
    void draw_one(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_two(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_three(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_four(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_five(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_six(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_seven(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_eight(ge211::Sprite_set& set, Position cell_index, bool is_hint);
    void draw_nine(ge211::Sprite_set& set, Position cell_index, bool is_hint);

    void draw_regular_one(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_two(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_three(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_four(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_five(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_six(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_seven(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_eight(ge211::Sprite_set& set, Position cell_index);
    void draw_regular_nine(ge211::Sprite_set& set, Position cell_index);

    void draw_hint_one(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_two(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_three(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_four(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_five(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_six(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_seven(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_eight(ge211::Sprite_set& set, Position cell_index);
    void draw_hint_nine(ge211::Sprite_set& set, Position cell_index);

};
