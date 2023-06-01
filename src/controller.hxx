#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    ge211::Dims<int> initial_window_dimensions() const override;
    void draw(ge211::Sprite_set& set) override;

private:
    Model model_;
    View view_;

    ge211::Posn<int> mouse_posn;
    void on_mouse_move(ge211::Posn<int>) override;

    void on_mouse_up(ge211::events::Mouse_button, ge211::Posn<int>) override;

    void on_key(ge211::Key) override;

};
