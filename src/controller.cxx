#include "controller.hxx"


// aliases
using Key = ge211::Key;
using Position = ge211::Posn<int>;


Controller::Controller(std::string board_string, std::string solution_string)
        : model_(board_string, solution_string),
          view_(model_),
          mouse_posn{0, 0}
{
    std::cout << "Controller constructor\n";
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

// updates the mouse_posn variable on mouse movement
void
Controller::on_mouse_move(ge211::Posn<int> position) {
    mouse_posn = position;
}


// when the mouse is clicked, update selected position
void
Controller::on_mouse_up(ge211::events::Mouse_button, ge211::Posn<int>) {
    // find out which square we just clicked on
    ge211::Posn<int> click_square = view_.mouse_posn_to_board(mouse_posn);
    // add a piece to that square

    model_.set_selected_cell(click_square);

}

void
Controller::on_key(Key key)
{


    // std::cout << "Key press: " << key.code() << "\n";
    if (key == Key::code('q')) {
        quit();
    }
    else if (key == Key::up() or key == Key::code('w')){
        // move up
        std::cout << "up\n";
        model_.move_select_up();
    }
    else if (key == Key::left() or key == Key::code('a')){
        std::cout << "left\n";
        model_.move_select_left();
    }
    else if (key == Key::right() or key == Key::code('d')){
        std::cout << "right\n";
        model_.move_select_right();
    }
    else if (key == Key::down() or key == Key::code('s')){
        std::cout << "down\n";
        model_.move_select_down();
    }

    if (key == ge211::Key::code(' ')){
        quit();
    }

}



void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

