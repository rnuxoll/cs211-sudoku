#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;
using Position = ge211::Posn<int>;

static int const grid_size = 72;

static Color const number_color {0, 0, 0};
static Color const value_square_color {255, 255, 255};
static Color const given_square_color {211,211,211};
static Color const selected_square_color {238,232,170};
static Color const reveal_square_color {0,0,255};

static Color const gridline_color {0, 0, 0};
static Color const red_dot_color{205, 92,92};
static Color const congrats_text_color{255,255,255};

View::View(Model const& model)
        : model_(model),
          white_square_sprite_({grid_size, grid_size},
                               value_square_color),
          shaded_square_sprite_({grid_size, grid_size},
                                given_square_color),
          selected_square_sprite_({grid_size, grid_size},
                                  selected_square_color),
          reveal_sprite_({grid_size, grid_size}, reveal_square_color),
          contradiction_dot_sprite_(grid_size / 8, red_dot_color),
          horizontal_grid_line_sprite_({grid_size, grid_size / 30},
                                       gridline_color),
          vertical_grid_line_sprite_({grid_size / 30, grid_size},
                                     gridline_color),
          thick_horizontal_grid_line_sprite_({grid_size, grid_size / 15},
                                             gridline_color),
          thick_vertical_grid_line_sprite_({grid_size / 15, grid_size},
                                           gridline_color)

{

}

void
View::draw(ge211::Sprite_set& set)
{
    if (model_.is_new_game()){
        draw_new_game(set);
    }
    else if (model_.is_game_over()){
        draw_congratulations(set);
    }
    else{
        draw_board(set);
    }
}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return {grid_size*BOARD_SIZE, grid_size*BOARD_SIZE};
}

// given a position of a square in board coordinates, convert it to
// screen (pixel) coordinates
ge211::Posn<int>
View::board_to_screen(ge211::Posn<int> board) const
{
    Position screen = {grid_size * board.x, grid_size * board.y};
    return screen;
}


// given a position of the top left corner of a square in screen coordinates
// convert it to board coordinates
ge211::Posn<int>
View::screen_to_board(ge211::Posn<int> screen) const
{
    Position board = {screen.x/grid_size, screen.y/grid_size};
    return board;
}

Position
View::cell_index_to_number_pos(Position index) const{
    Position screen_pos = {grid_size * index.x + 10, grid_size * index.y - 20};
    return screen_pos;
}


// given the position of the mouse in board coordinates,
// convert it to board coordinates
ge211::Posn<int>
View::mouse_posn_to_board(View::Position mouse_posn) const
{
    // round down mouse_posn x and y to the nearest multiple of grid_size
    // these are the coordinates of the top left corner of the box that
    // the mouse is in pixels
    // now call screen_to_board on these board coordinates
    int screen_x = (mouse_posn.x / grid_size ) * grid_size;
    int screen_y = (mouse_posn.y / grid_size) * grid_size;
    Position screen_pos = {screen_x, screen_y};

    Position board_pos = screen_to_board(screen_pos);
    return board_pos;
}

void View::draw_board(ge211::Sprite_set& set){

    Board our_board = model_.get_board();
    Position selected = model_.get_selected_cell();

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            Cell cell = our_board.get_cell_reference(i, j);
            bool is_selected = false;

            if (selected == Position{ i, j} ){
                is_selected = true;
            }
            draw_cell(set, cell, is_selected);
        }
    }
}

void View::draw_new_game(ge211::Sprite_set& set)
{
    draw_for_new_game(set, {0,2});
    draw_press(set, {0,3});
    draw_difficulty_levels(set, {2,4});
}

void View::draw_congratulations(ge211::Sprite_set& set)
{
    draw_you_win(set, {0,1});
    draw_new_game(set);

    // for (int r = 0; r < 9; r++){
    //     for (int c = 0; c < 9; c++){
    //         Cell blank_cell = Cell(0, {c, r});
    //         draw_cell(set, blank_cell, false);
    //     }
    // }



    // draw y in 3, 2
    // draw_y(set, {3,2});
    // draw_o(set, {4, 2});
    // draw_u(set, {5,2});
    // draw_w(set,{3,3});
    // draw_i(set,{4,3});
    // draw_n(set,{5,3});
    //
    // draw_p(set,{1,5});
    // draw_r(set, {2,5});
    // draw_e(set, {3,5});
    // draw_s(set, {4,5});
    // draw_s(set,{5,5});
    //
    // // draw_apostrophe(set,{6,5});
    // draw_n(set,{7,5});
    // //draw_apostrophe(set,{8,5});
    //
    // draw_f(set,{1,6});
    // draw_o(set,{2,6});
    // draw_r(set, {3,6});
    //
    // draw_n(set,{5,6});
    // draw_e(set,{6,6});
    // draw_w(set,{7,6});
    //
    // draw_g(set,{2,7});
    // draw_a(set, {3,7});
    // draw_m(set,{4,7});
    // draw_e(set,{5,7});
}


void View::draw_you_win(ge211::Sprite_set& set, View::Position start_cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(start_cell_index);
    set.add_sprite(you_win_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(congrats_text_color);
    number_builder.message("You win");
    you_win_sprite_.reconfigure(number_builder);
}


void View::draw_for_new_game(
        ge211::Sprite_set& set,
        Position start_cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(start_cell_index);
    set.add_sprite(for_new_game_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(congrats_text_color);
    number_builder.message("For new game,");
    for_new_game_sprite_.reconfigure(number_builder);
}

void View::draw_press(ge211::Sprite_set& set, Position start_cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(start_cell_index);
    set.add_sprite(press_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(congrats_text_color);
    number_builder.message("press: ");
    press_sprite_.reconfigure(number_builder);
}


void View::draw_difficulty_levels(
        ge211::Sprite_set& set,
        View::Position start_cell_index)
{
    Position beginner_pos_in_screen = cell_index_to_number_pos
            (start_cell_index);

    Position normal_pos_in_screen = cell_index_to_number_pos(start_cell_index
            .down_by(1));

    Position expert_pos_in_screen = cell_index_to_number_pos(start_cell_index
            .down_by(2));

    set.add_sprite(b_beginner_sprite_, beginner_pos_in_screen, TEXT_Z);
    set.add_sprite(n_normal_sprite_, normal_pos_in_screen, TEXT_Z);
    set.add_sprite(e_expert_sprite_, expert_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder beginner_builder(sans72_);
    beginner_builder.color(congrats_text_color);
    beginner_builder.message("B-Beginner");

    ge211::Text_sprite::Builder normal_builder(sans72_);
    normal_builder.color(congrats_text_color);
    normal_builder.message("N-Normal");

    ge211::Text_sprite::Builder expert_builder(sans72_);
    expert_builder.color(congrats_text_color);
    expert_builder.message("E-Expert");

    b_beginner_sprite_.reconfigure(beginner_builder);
    n_normal_sprite_.reconfigure(normal_builder);
    e_expert_sprite_.reconfigure(expert_builder);
}


void View::draw_cell(ge211::Sprite_set& set, Cell cell, bool selected)
{
    // draw squares
    Position cell_index = cell.get_index();
    Position corner_in_screen = board_to_screen(cell_index);

    // draw appropriate square color
    if (selected){
        set.add_sprite(selected_square_sprite_, corner_in_screen);
    }
    else if (cell.is_fixed()){
        set.add_sprite(shaded_square_sprite_, corner_in_screen);
    } else {
        set.add_sprite(white_square_sprite_, corner_in_screen);
    }
    // draw contradiction dot if appropriate
    if (cell.is_inconsistent()){
        set.add_sprite(contradiction_dot_sprite_, corner_in_screen, 4);
    }


    // draw thick grid lines
    Position lower_hor_line_pos = cell_index.down_by(1);
    Position lower_ver_line_pos = cell_index.right_by(1);

    if (((cell_index.x + 1) % 3 == 0) && (cell_index.x !=0)) {

        set.add_sprite(thick_vertical_grid_line_sprite_, board_to_screen
        (lower_ver_line_pos), 1);
    }

    if (((cell_index.y + 1 ) % 3 == 0) && (cell_index.y !=0)) {
        set.add_sprite(thick_horizontal_grid_line_sprite_,
                       board_to_screen(lower_hor_line_pos), 1);
    }

    // Draw normal thickness grid lines
    set.add_sprite(horizontal_grid_line_sprite_,
                   board_to_screen(lower_hor_line_pos), 1);
    set.add_sprite(vertical_grid_line_sprite_,
                   board_to_screen(lower_ver_line_pos), 1);

    // draw number inside
    switch (cell.get_value()){
    case 1:
        draw_one(set, cell_index, cell.is_hint());
        break;
    case 2:
        draw_two(set, cell_index, cell.is_hint());
        break;
    case 3:
        draw_three(set, cell_index, cell.is_hint());
        break;
    case 4:
        draw_four(set, cell_index, cell.is_hint());
        break;
    case 5:
        draw_five(set, cell_index, cell.is_hint());
        break;
    case 6:
        draw_six(set, cell_index, cell.is_hint());
        break;
    case 7:
        draw_seven(set, cell_index, cell.is_hint());
        break;
    case 8:
        draw_eight(set, cell_index, cell.is_hint());
        break;
    case 9:
        draw_nine(set, cell_index, cell.is_hint());
        break;
    }
}

void View::draw_one(ge211::Sprite_set& set, Position cell_index, bool is_hint){
    if (is_hint) {
        draw_hint_one(set, cell_index);
    } else {
        draw_regular_one(set, cell_index);
    }
}

void View::draw_two(ge211::Sprite_set& set, Position cell_index, bool is_hint){
    if (is_hint) {
        draw_hint_two(set, cell_index);
    } else {
        draw_regular_two(set, cell_index);
    }
}

void View::draw_three(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    if (is_hint) {
        draw_hint_three(set, cell_index);
    } else {
        draw_regular_three(set, cell_index);
    }
}

void View::draw_four(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    if (is_hint) {
        draw_hint_four(set, cell_index);
    } else {
        draw_regular_four(set, cell_index);
    }
}

void View::draw_five(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    if (is_hint) {
        draw_hint_five(set, cell_index);
    } else {
        draw_regular_five(set, cell_index);
    }
}

void View::draw_six(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    if (is_hint) {
        draw_hint_six(set, cell_index);
    } else {
        draw_regular_six(set, cell_index);
    }
}

void View::draw_seven(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    if (is_hint) {
        draw_hint_seven(set, cell_index);
    } else {
        draw_regular_seven(set, cell_index);
    }
}

void View::draw_eight(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    if (is_hint) {
        draw_hint_eight(set, cell_index);
    } else {
        draw_regular_eight(set, cell_index);
    }
}

void View::draw_nine(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    if (is_hint) {
        draw_hint_nine(set, cell_index);
    } else {
        draw_regular_nine(set, cell_index);
    }
}


void View::draw_regular_two(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(two_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("2");
    two_sprite_.reconfigure(number_builder);
}

void View::draw_regular_three(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(three_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("3");
    three_sprite_.reconfigure(number_builder);
}

void View::draw_regular_four(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(four_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("4");
    four_sprite_.reconfigure(number_builder);
}

void View::draw_regular_five(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(five_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("5");
    five_sprite_.reconfigure(number_builder);
}

void View::draw_regular_six(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(six_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("6");
    six_sprite_.reconfigure(number_builder);
}

void View::draw_regular_seven(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(seven_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("7");
    seven_sprite_.reconfigure(number_builder);
}

void View::draw_regular_eight(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(eight_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("8");
    eight_sprite_.reconfigure(number_builder);
}

void View::draw_regular_nine(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(nine_sprite_, number_pos_in_screen, TEXT_Z);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("9");
    nine_sprite_.reconfigure(number_builder);
}

void View::draw_hint_one(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(one_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("1");
    one_hint_sprite_.reconfigure(number_builder);
}

void View::draw_hint_two(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(two_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("2");
    two_hint_sprite_.reconfigure(number_builder);
}
void View::draw_hint_three(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(three_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("3");
    three_hint_sprite_.reconfigure(number_builder);
}

void View::draw_hint_four(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(four_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("4");
    four_hint_sprite_.reconfigure(number_builder);
}

void View::draw_hint_five(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(five_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("5");
    five_hint_sprite_.reconfigure(number_builder);
}

void View::draw_hint_six(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(six_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("6");
    six_hint_sprite_.reconfigure(number_builder);
}

void View::draw_hint_seven(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(seven_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("7");
    seven_hint_sprite_.reconfigure(number_builder);
}

void View::draw_hint_eight(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(eight_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("8");
    eight_hint_sprite_.reconfigure(number_builder);
}

void View::draw_hint_nine(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(nine_hint_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(reveal_square_color);
    number_builder.message("9");
    nine_hint_sprite_.reconfigure(number_builder);
}


void View::draw_regular_one(ge211::Sprite_set& set, View::Position cell_index)
{
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    set.add_sprite(one_sprite_, number_pos_in_screen, TEXT_Z);
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("1");
    one_sprite_.reconfigure(number_builder);
}

