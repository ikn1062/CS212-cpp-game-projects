#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, ge211::Position);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    ge211::Position screen_to_board_(ge211::Position screen_pos) const;
    ge211::Position board_to_screen_(ge211::Position board_pos) const;

private:
    Model const& model_;

    // TODO: Add any private members you need, such as helper functions
    // or sprites.

    ge211::Rectangle_sprite const background_blocks_;
    ge211::Circle_sprite const light_token_;
    ge211::Circle_sprite const dark_token_;
    ge211::Circle_sprite const red_token_;
    ge211::Circle_sprite const grey_token_;
    ge211::Circle_sprite const light_token_1_;
    ge211::Circle_sprite const dark_token_1_;
    ge211::Rectangle_sprite const background_fill_;
    ge211::Rectangle_sprite const red_token_1_;
};