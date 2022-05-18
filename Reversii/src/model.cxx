#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    compute_next_moves_();
}

Rectangle Model::board() const
{
    return board_.all_positions();
}

Player Model::operator[](Position pos) const
{
    return board_[pos];
}

Move const* Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end())
        return nullptr;
    else
        return &*i;
}

void Model::play_move(Position pos)
{
    if (is_game_over())
        throw Client_logic_error("Model::play_move: game over");

    Move const* movep = find_move(pos);
    if (!movep)
        throw Client_logic_error("Model::play_move: no such move");

    if (movep != nullptr) {really_play_move_(*movep);}
}

//
// BELOW ARE *OPTIONAL* HELPER FUNCTIONS
//

Position_set Model::find_flips_(Position current, Dimensions dir) const
{
    Position_set p_set; // Sets up a Position Set to return

    Player p1 = Model::turn(); // Sets the current player as p1
    current = {current.x + dir.width, current.y + dir.height};

    while(true){
        if (current.x < 0 || current.y < 0 || current.x >= board().width
        || current.y >= board().height){
            p_set.clear();
            break;
        }

        Player p2 = Model::operator[](current);
        if (p2 == Player::neither){
            p_set.clear();
            break;
        }
        if (p2 == other_player(p1)) {p_set[{current}] = true;}
        if (p2 == p1) {return p_set;}

        current = {current.x + dir.width, current.y + dir.height};
    }
    return p_set;
}

Position_set Model::evaluate_position_(Position pos) const
{
    Position_set p_set;
    if (Model::operator[](pos) != Player::neither) {return p_set;}

    for (ge211::Dimensions dim : Board::all_directions()){
        if (find_flips_(pos,dim).empty()){
            p_set.empty();
        } else {p_set |= find_flips_(pos,dim);}
    }
    if (!p_set.empty()) {p_set[{pos}] = true;}
    return p_set;
}

void Model::compute_next_moves_()
{
    next_moves_.clear();

    for (ge211::Position pos : board_.center_positions()){
        Player player = Model::operator[](pos);
        if (player == Player::neither){next_moves_[pos] = {pos};}
    }
    if (!next_moves_.empty()) {return;}

    Position_set p_set;
    for (ge211::Position pos : board_.all_positions()){
        p_set = evaluate_position_(pos);
        if (!p_set.empty()) {next_moves_[pos] = p_set;}
    }
}

bool Model::advance_turn_()
{
    turn_ = other_player(turn_);
    compute_next_moves_();
    return(!next_moves_.empty());
}

void Model::set_game_over_()
{
    turn_ = Player::neither;

    size_t count_l = board_.count_player(Player::light);
    size_t count_d = board_.count_player(Player::dark);

    if (count_l > count_d) {winner_ = Player::light;}
    if (count_d > count_l) {winner_ = Player::dark;}
}

void Model::really_play_move_(Move move)
{
    if (is_game_over()) return;

    board_.set_all(move.second,turn_);
    if (!advance_turn_()){
        if (!advance_turn_()){
            set_game_over_();
        }
    }
}