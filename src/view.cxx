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

View::View(Model const& model)
        : model_(model),
          white_square_sprite({grid_size, grid_size}, value_square_color),
          shaded_square_sprite({grid_size, grid_size}, given_square_color),
          selected_square_sprite({grid_size, grid_size}, selected_square_color),
          reveal_sprite({grid_size, grid_size}, reveal_square_color),
          contradiction_dot_sprite(grid_size / 8, red_dot_color),
          horizontal_grid_line_sprite({grid_size, grid_size / 30},
                                      gridline_color),
          vertical_grid_line_sprite({grid_size / 30, grid_size},
                                    gridline_color)

          // todo initialize all of the other sprites
{
    // std::cout << "View Constructor\n";

}

void
View::draw(ge211::Sprite_set& set)
{
    if (model_.is_game_over()){
        draw_congratulations(set);
    }
    else{
        draw_board(set);
    }
}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return {grid_size*9, grid_size*9};
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
            Position cell_index = cell.get_index();
            bool is_selected = false;

            if (selected == Position{ i, j} ){
                is_selected = true;
            }
            draw_cell(set, cell, is_selected);
        }
    }
}

void View::draw_congratulations(ge211::Sprite_set& set)
{
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            Cell blank_cell = Cell(0, {c, r});
            draw_cell(set, blank_cell, false);
        }
    }
    // draw y in 3, 2
    draw_y(set, {3,2});
    draw_o(set, {4, 2});
    draw_u(set, {5,2});
    draw_w(set,{3,3});
    draw_i(set,{4,3});
    draw_n(set,{5,3});

    draw_p(set,{1,5});
    draw_r(set, {2,5});
    draw_e(set, {3,5});
    draw_s(set, {4,5});
    draw_s(set,{5,5});

    // draw_apostrophe(set,{6,5});
    draw_n(set,{7,5});
    //draw_apostrophe(set,{8,5});

    draw_f(set,{1,6});
    draw_o(set,{2,6});
    draw_r(set, {3,6});

    draw_n(set,{5,6});
    draw_e(set,{6,6});
    draw_w(set,{7,6});

    draw_g(set,{2,7});
    draw_a(set, {3,7});
    draw_m(set,{4,7});
    draw_e(set,{5,7});
}


// Todo make this check the indexes of the cell and make thicker gridlines as
//  necessary
void View::draw_cell(ge211::Sprite_set& set, Cell cell, bool selected)
{
    // draw squares
    Position cell_index = cell.get_index();
    Position corner_in_screen = board_to_screen(cell_index);

    // draw appropriate square color
    if (selected){
        set.add_sprite(selected_square_sprite, corner_in_screen);
    }
    else if (cell.is_fixed()){
        set.add_sprite(shaded_square_sprite, corner_in_screen);
    } else {
        set.add_sprite(white_square_sprite, corner_in_screen);
    }
    // draw contradiction dot if appropriate
    if (cell.is_inconsistent()){
        set.add_sprite(contradiction_dot_sprite, corner_in_screen, 4);
    }

    if (cell.is_hint()) {
        set.add_sprite(reveal_sprite, corner_in_screen,3);
    }
    // draw grid lines
    Position lower_hor_line_pos = cell_index.down_by(1);
    Position lower_ver_line_pos = cell_index.right_by(1);
    set.add_sprite(horizontal_grid_line_sprite,
                   board_to_screen(lower_hor_line_pos), 1);
    set.add_sprite(vertical_grid_line_sprite,
                   board_to_screen(lower_ver_line_pos), 1);


    // draw number inside
    switch (cell.get_value()){
    case 1:
        draw_one(set, cell_index, cell.is_hint());

        break;
    case 2:
        draw_two(set, cell_index, false);
        break;
    case 3:
        draw_three(set, cell_index, false);
        break;
    case 4:
        draw_four(set, cell_index, false);
        break;
    case 5:
        draw_five(set, cell_index, false);
        break;
    case 6:
        draw_six(set, cell_index, false);
        break;
    case 7:
        draw_seven(set, cell_index, false);
        break;
    case 8:
        draw_eight(set, cell_index, false);
        break;
    case 9:
        draw_nine(set, cell_index, false);
        break;
    }
}

void View::draw_one(ge211::Sprite_set& set, Position cell_index, bool is_hint){

    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(one_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    if (is_hint) {
        number_builder.color(reveal_square_color);
    } else {
        number_builder.color(number_color);
    }
    number_builder.message("1");
    one_sprite.reconfigure(number_builder);
    /*if (is_hint) {
        number_builder.color(reveal_square_color);
        one_sprite.reconfigure(number_builder);

    }*/
}

void View::draw_two(ge211::Sprite_set& set, Position cell_index, bool is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(two_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("2");
    two_sprite.reconfigure(number_builder);
}

void View::draw_three(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(three_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("3");
    three_sprite.reconfigure(number_builder);
}

void View::draw_four(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(four_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("4");
    four_sprite.reconfigure(number_builder);
}

void View::draw_five(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(five_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("5");
    five_sprite.reconfigure(number_builder);
}

void View::draw_six(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(six_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("6");
    six_sprite.reconfigure(number_builder);
}

void View::draw_seven(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(seven_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("7");
    seven_sprite.reconfigure(number_builder);
}

void View::draw_eight(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(eight_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("8");
    eight_sprite.reconfigure(number_builder);
}

void View::draw_nine(ge211::Sprite_set& set, Position cell_index, bool
is_hint){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(nine_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("9");
    nine_sprite.reconfigure(number_builder);
}

void View::draw_y(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(y_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("Y");
    y_sprite.reconfigure(number_builder);
}

void View::draw_o(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(o_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("O");
    o_sprite.reconfigure(number_builder);
}

void View::draw_u(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(u_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("U");
    u_sprite.reconfigure(number_builder);
}

void View::draw_w(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    number_pos_in_screen = number_pos_in_screen.right_by(-6);

    set.add_sprite(w_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("W");
    w_sprite.reconfigure(number_builder);
}

void View::draw_i(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);
    number_pos_in_screen = number_pos_in_screen.right_by(10);

    set.add_sprite(i_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("I");
    i_sprite.reconfigure(number_builder);
}

void View::draw_n(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(n_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("N");
    n_sprite.reconfigure(number_builder);
}

void View::draw_p(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(p_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("P");
    p_sprite.reconfigure(number_builder);
}

void View::draw_r(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(r_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("R");
    r_sprite.reconfigure(number_builder);
}

void View::draw_e(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(e_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("E");
    e_sprite.reconfigure(number_builder);
}

void View::draw_s(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(s_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("S");
    s_sprite.reconfigure(number_builder);
}

void View::draw_apostrophe(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(apos_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("'");
    apos_sprite.reconfigure(number_builder);
}

void View::draw_f(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(f_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("F");
    f_sprite.reconfigure(number_builder);
}

void View::draw_g(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(g_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("G");
    g_sprite.reconfigure(number_builder);
}

void View::draw_a(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(a_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("A");
    a_sprite.reconfigure(number_builder);
}

void View::draw_m(ge211::Sprite_set& set, Position cell_index){
    Position number_pos_in_screen = cell_index_to_number_pos(cell_index);

    set.add_sprite(m_sprite, number_pos_in_screen,5);

    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("M");
    m_sprite.reconfigure(number_builder);
}