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
static Color const gridline_color {0, 0, 0};
static Color const red_dot_color{205, 92,92};

View::View(Model const& model)
        : model_(model),
          white_square_sprite({grid_size, grid_size}, value_square_color),
          shaded_square_sprite({grid_size, grid_size}, given_square_color),
          selected_square_sprite({grid_size, grid_size}, selected_square_color),
          contradiction_dot_sprite(grid_size / 8, red_dot_color),
          horizontal_grid_line_sprite({grid_size, grid_size / 30},
                                      gridline_color),
          vertical_grid_line_sprite({grid_size / 30, grid_size},
                                    gridline_color)

          // todo initialize all of the other sprites
{
    std::cout << "View Constructor\n";

}

void
View::draw(ge211::Sprite_set& set)
{
    draw_board(set);
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


    model_.print_board();

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            Cell cell = our_board.get_cell(i, j);
            Position cell_index = cell.get_index();
            bool is_selected = false;

            if (selected == Position{ i, j} ){
                is_selected = true;
            }
            draw_cell(set, cell, is_selected);
        }
    }
}


// Todo make this check the indexes of the cell and make thicker gridlines as
//  necessary
void View::draw_cell(ge211::Sprite_set& set, Cell cell, bool selected)
{
    // draw squares
    Position cell_index = cell.get_index();
    Position corner = board_to_screen(cell_index);

    if (selected){
        set.add_sprite(selected_square_sprite, corner);
    }
    else {
        set.add_sprite(white_square_sprite, corner);
    }

    // draw grid lines
    Position lower_hor_line_pos = cell_index.down_by(1);
    Position lower_ver_line_pos = cell_index.right_by(1);
    set.add_sprite(horizontal_grid_line_sprite,
                   board_to_screen(lower_hor_line_pos), 1);
    set.add_sprite(vertical_grid_line_sprite,
                   board_to_screen(lower_ver_line_pos), 1);


    // draw number inside
    if (cell.get_value() == 1){
        // std::cout << "value is 1\n";
        draw_one(set, corner, false);
    }
}


// void View::draw_value_square(ge211::Sprite_set& set,
//         View::Position box_coord)
// {
//     // draw squares
//     Position corner = board_to_screen(box_coord);
//     std::cout << "Drawing white square in corner: " << corner << "\n";
//     set.add_sprite(white_square_sprite, board_to_screen(box_coord));
//
//     // draw grid lines
//     Position lower_hor_line_pos = box_coord.down_by(1);
//     Position lower_ver_line_pos = box_coord.right_by(1);
//     set.add_sprite(horizontal_grid_line_sprite,
//                    board_to_screen(lower_hor_line_pos), 1);
//     set.add_sprite(vertical_grid_line_sprite,
//                    board_to_screen(lower_ver_line_pos), 1);
// }

void View::draw_one(ge211::Sprite_set& set, Position box_coord, bool is_hint){
    ge211::Text_sprite::Builder number_builder(sans72_);
    number_builder.color(number_color);
    number_builder.message("1");

    Position screen_pos = board_to_screen(box_coord);

    ge211::Text_sprite modified_one_sprite = one_sprite;
    modified_one_sprite.reconfigure(number_builder);

    // set.add_sprite(modified_one_sprite, screen_pos, 1);
}