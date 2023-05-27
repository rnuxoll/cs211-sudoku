#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;
using Position = ge211::Posn<int>;

static int const grid_size = 72;

static Color const number_color {0, 0, 0};
static Color const value_square_color {255, 255, 255};
static Color const given_square_color {211,211,211};
static Color const gridline_color {0, 0, 0};
static Color const red_dot_color{205, 92,92};

View::View(Model const& model)
        : model_(model),
          white_square_sprite({grid_size, grid_size}, value_square_color),
          shaded_square_sprite({grid_size, grid_size}, given_square_color),
          contradiction_dot_sprite(grid_size / 8, red_dot_color),
          horizontal_grid_line_sprite({grid_size, grid_size / 30},
                                      gridline_color),
          vertical_grid_line_sprite({grid_size / 30, grid_size},
                                    gridline_color),
          one_sprite("1", sans72),
          two_sprite("2", sans72),
          three_sprite("3", sans72),
          four_sprite("4", sans72),
          five_sprite("5", sans72),
          six_sprite("6", sans72),
          seven_sprite("7", sans72),
          eight_sprite("8", sans72),
          nine_sprite("9", sans72)
{

}

void
View::draw(ge211::Sprite_set& set)
{
    // draw_board(set);
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
    for (Position square : model_.all_positions()){
        // draw squares
        set.add_sprite(white_square_sprite, board_to_screen(square));

        // draw grid lines
        Position lower_hor_line_pos = square.down_by(1);
        Position lower_ver_line_pos = square.right_by(1);
        set.add_sprite(horizontal_grid_line_sprite,
                       board_to_screen(lower_hor_line_pos), 1);
        set.add_sprite(vertical_grid_line_sprite,
                       board_to_screen(lower_ver_line_pos), 1);
    }
}

void View::draw_cell(ge211::Sprite_set& set, Cell cell)
{

}