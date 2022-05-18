#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
        , mouse_pos_{0,0}
{ }

void Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites,mouse_pos_);
}

ge211::Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}
void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position pos) {
    mouse_pos_ = pos;
    pos = view_.screen_to_board_(pos);
    if (model_.find_move(pos) != nullptr) {model_.play_move(pos);}
}

void Controller::on_mouse_move(ge211::Position pos) {
    mouse_pos_ = pos;
}