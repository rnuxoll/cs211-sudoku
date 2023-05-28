#include "controller.hxx"

Controller::Controller()
        : model_(),
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
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

