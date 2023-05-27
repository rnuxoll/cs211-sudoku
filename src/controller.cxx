#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{
    std::cout << "Controller constructor\n";
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}



