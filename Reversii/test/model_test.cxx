#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

// These pass with the starter code and should continue
// to pass.

TEST_CASE("Passes with starter code")
{
    Model m(8, 8);
    CHECK( m.board() == Rectangle{0, 0, 8, 8} );
    CHECK_FALSE( m.is_game_over() );
    CHECK( m.turn() == Player::dark );
    CHECK( m.winner() == Player::neither );
    CHECK( m[{0, 0}] == Player::neither );
    CHECK( m.find_move({0, 0}) == nullptr );
    CHECK_THROWS_AS( m.play_move({0, 0}), Client_logic_error );
}

// This fails with the starter code, but should pass.
TEST_CASE("Fails with starter code")
{
    Model m(6);
    CHECK( m.find_move({2, 2}) );
}

// This fails with the starter code, but should pass.
TEST_CASE("Throws with starter code")
{
    Model m(4);
    m.play_move({1, 1});
}


// YOU NEED MANY MORE TESTS!
TEST_CASE("4x4 Board")
{
    Model m(4);
    CHECK(m.board() == Rectangle{0, 0, 4, 4});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    m.play_move({1, 1});
    CHECK(m.turn() == Player::light);
    m.play_move({2, 1});
    CHECK(m.turn() == Player::dark);
    m.play_move({2, 2});
    CHECK(m.turn() == Player::light);
    CHECK(m.winner() == Player::neither);
    CHECK_FALSE( m.is_game_over() );
    CHECK( m[{1, 2}] == Player::neither );
    CHECK( m.find_move({1, 2}) );
    m.play_move({1, 2});

    m.play_move({2,0});
    CHECK( m[{2, 1}] == Player::dark);
    m.play_move({1,0});
    CHECK( m[{1, 1}] == Player::light);
    m.play_move({0,0});
    CHECK( m[{1, 1}] == Player::dark);
    CHECK( m[{1, 0}] == Player::dark);
    m.play_move({3,0});
    m.play_move({3,2});
    m.play_move({1,3});
    m.play_move({0,3});
    m.play_move({0,2});
    m.play_move({0,1});
    m.play_move({2,3});
    m.play_move({3,3});
    CHECK_FALSE( m.is_game_over() );
    m.play_move({3,1});
    CHECK( m.is_game_over() );
    CHECK(m.winner() == Player::light);
}

TEST_CASE("2x2 Board"){
    Model m(2);
    CHECK(m.board() == Rectangle{0, 0, 2, 2});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    m.play_move({1, 1});
    CHECK(m.turn() == Player::light);
    m.play_move({1, 0});
    CHECK(m.turn() == Player::dark);
    m.play_move({0, 0});
    CHECK(m.turn() == Player::light);
    m.play_move({0, 1});
    CHECK( m.is_game_over() );
    CHECK_THROWS_AS( m.play_move({0, 0}), Client_logic_error );
    CHECK_THROWS_AS( m.play_move({1, 0}), Client_logic_error );
    CHECK(m.winner() == Player::neither);
}

TEST_CASE("6x6 Board")
{
    Model m(6);
    CHECK(m.board() == Rectangle{0, 0, 6, 6});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    m.play_move({2, 2});
    CHECK(m.turn() == Player::light);
    m.play_move({2, 3});
    CHECK(m.turn() == Player::dark);
    m.play_move({3, 3});
    CHECK(m.turn() == Player::light);
    m.play_move({3, 2});
}

TEST_CASE("Test 2")
{
    Model m(4);
    CHECK(m.board() == Rectangle{0, 0, 4, 4});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    m.play_move({2, 1});
    CHECK(m.turn() == Player::light);
    m.play_move({1, 1});
    CHECK(m.turn() == Player::dark);
    m.play_move({2, 2});
    CHECK(m.turn() == Player::light);
    m.play_move({1, 2});
    CHECK( m[{2,1}] == Player::dark);
    CHECK( m[{2,2}] == Player::dark);
    CHECK( m[{1,1}] == Player::light);
    CHECK( m[{1,2}] == Player::light);
    CHECK_THROWS_AS(m.play_move({2, 1}), Client_logic_error);
}

TEST_CASE("Boundaries")
{
    Model m(4);
    CHECK(m.board() == Rectangle{0, 0, 4, 4});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    CHECK_THROWS_AS(m.play_move({-1, -1}), Client_logic_error);
    CHECK_THROWS_AS(m.play_move({5, 5}), Client_logic_error);
    CHECK_THROWS_AS(m.play_move({4, 4}), Client_logic_error);

    CHECK( m.find_move({0, 0}) == nullptr );
    CHECK( m.find_move({3, 3}) == nullptr );
}
