#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static int const grid_size = 72;

static Color const number_color {0, 0, 0};
static Color const value_square_color {255, 255, 255};
static Color const given_square_color {211,211,211};
static Color const gridline_color {0, 0, 0};
static Color const red_dot_color{205, 92,92};

View::View(Model const& model)
        : model_(model)
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
}
