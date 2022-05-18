#include "view.hxx"

static ge211::Color const
        dark   = ge211::Color::black(),
        light = ge211::Color::white(),
        red  = ge211::Color::medium_red(),
        back = ge211::Color::medium_green().darken(0.5),
        grey  = ge211::Color::black().blend(0.5,ge211::Color::white()),
        light_1  = ge211::Color::white().fade_out(0.5),
        back_ = ge211::Color::medium_yellow().lighten(0.5),
        dark_1 = ge211::Color::black().fade_out(0.5),
        red_1 = ge211::Color::medium_red().lighten(0.5);

// Convenient type aliases:
using Dimensions = ge211::Dimensions;
using Position   = ge211::Position;
using Color      = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 100;

View::View(Model const& model)
        : model_(model)
        // You may want to add sprite initialization here
        , background_blocks_({(grid_size/10 )*9, (grid_size/10)*9},back)
        , light_token_((grid_size/6)*2,light)
        , dark_token_((grid_size/6)*2,dark)
        , red_token_((grid_size/6)*2,red)
        , grey_token_((grid_size/6)*2,grey)
        , light_token_1_((grid_size/8)*2,light_1)
        , dark_token_1_((grid_size/8)*2,dark_1)
        , background_fill_(View::initial_window_dimensions(),back_)
        , red_token_1_({(grid_size/10 )*9, (grid_size/10)*9},red_1)
{ }

void View::draw(Sprite_set& set, ge211::Position posn)
{
    // TODO, PROBABLY
    // Set up the background
    set.add_sprite(background_fill_, {0, 0});

    // Set up the green grid
    for (Position pos : model_.board()) {
        Position pos_1 = board_to_screen_(pos);
        pos_1 = {pos_1.x + grid_size / 20, pos_1.y + grid_size / 20};
        set.add_sprite(background_blocks_, pos_1, 1);
    }

    // Follow the mouse
    if (model_.turn() != Player::neither) {
        if (!model_.is_game_over()) {
            Position pos_mouse = posn;
            if (model_.turn() == Player::light) {
                set.add_sprite(light_token_1_, pos_mouse, 10);
            }
            if (model_.turn() == Player::dark) {
                set.add_sprite(dark_token_1_, pos_mouse, 10);
            }

            for (Position pos : model_.board()) {
                Position pos_1 = board_to_screen_(pos);
                pos_1 = {pos_1.x + 4 * grid_size / 20,
                         pos_1.y + 4 * grid_size / 20};
                if (model_.operator[](pos) == Player::light) {
                    set.add_sprite(light_token_, pos_1, 3);
                }
                if (model_.operator[](pos) == Player::dark) {
                    set.add_sprite(dark_token_, pos_1, 3);
                }
            }
        }
    }
    if (model_.is_game_over()){
        for (Position pos : model_.board()){
            Position pos_1 = board_to_screen_(pos);
            pos_1 = {pos_1.x + 4 * grid_size / 20,
                     pos_1.y + 4 * grid_size / 20};
            if (model_.operator[](pos) != model_.winner()){
                set.add_sprite(grey_token_, pos_1, 5);
            }
            if (model_.operator[](pos) == model_.winner()){
                if (model_.winner() == Player::light){
                    set.add_sprite(light_token_, pos_1, 5);
                }
                if (model_.winner() == Player::dark){
                    set.add_sprite(dark_token_, pos_1, 5);
                }
            }
        }
    }
    for (Position pos : model_.board()) {
        if (model_.find_move(pos) != nullptr) {
            Move move_1 = *model_.find_move(pos);
            Position pos_2  = board_to_screen_(pos);
            pos_2 = {pos_2.x + 4 * grid_size / 20,
                     pos_2.y + 4 * grid_size / 20};
            set.add_sprite(red_token_, pos_2, 5);
            Position mouse_p_stb = screen_to_board_(posn);
            if (pos.x == mouse_p_stb.x && pos.y == mouse_p_stb.y) {
                for (Position pos_3 : move_1.second) {
                    pos_3 = board_to_screen_(pos_3);
                    Position pos_4 = {pos_3.x + grid_size / 20,
                                      pos_3.y + grid_size / 20};
                    set.add_sprite(red_token_1_, pos_4, 2);
                }
            }
        }
    }
}


Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}
ge211::Position View::screen_to_board_(Position pos) const
{
    return{pos.x / grid_size, pos.y / grid_size};
}

ge211::Position View::board_to_screen_(Position pos) const
{
    return{pos.x * grid_size, pos.y * grid_size};
}