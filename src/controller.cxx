#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{
    std::cout << "Controller constructor\n";
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}



