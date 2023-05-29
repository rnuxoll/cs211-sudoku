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

    std::cout << "Key press: " << key.code() << "\n";
    model_.print_board();

    std::cout << "Printed board\n";

    if (key == Key::code('q')) {
        quit();
    }
    // todo delete this
    // testing clause, set the top left corner to row_inconsistent if i is pressed
    // else if (key == Key::code('i')){
    //     std::cout << "setting the top left to be row_inconsistent\n";
    //     Board& board_ref = model_.get_board_reference();
    //     Cell& top_left = board_ref.get_cell_reference(0, 0);
    //     top_left.set_inconsistent(true);
    //
    //     std::cout << "final value of set row_inconsistent = " << top_left
    //     .is_inconsistent() << "\n";
    // }
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
    // if user presses backspace
    else if (key == Key::code(8)){
        model_.attempt_clear_selected_cell();
    }

    // if user presses 1
    else if (key == Key::code(49)){
        model_.process_numerical_input(1);
    }
    // if user presses 2
    else if (key == Key::code(50)){
        model_.process_numerical_input(2);
    }
    else if (key == Key::code(51)){
        model_.process_numerical_input(3);
    }
    else if (key == Key::code(52)){
        model_.process_numerical_input(4);
    }
    else if (key == Key::code(53)){
        model_.process_numerical_input(5);
    }
    else if (key == Key::code(54)){
        model_.process_numerical_input(6);
    }
    else if (key == Key::code(55)){
        model_.process_numerical_input(7);
    }
    else if (key == Key::code(56)){
        model_.process_numerical_input(8);
    }
    else if (key == Key::code(57)){
        model_.process_numerical_input(9);
    }

    if (key == ge211::Key::code(' ')){
        quit();
    }


    // after all key presses have been processed and the model has been
    // updated, it is now time to update the inconsistencies

    model_.print_board();
    Board& my_board = model_.get_board_reference();
    my_board.mark_duplicates();

    std::cout << "exiting on key\n";
}



void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

