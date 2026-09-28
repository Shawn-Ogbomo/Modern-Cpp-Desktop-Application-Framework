#include "../include/menu.hpp"

namespace B_N = Button_Names;
namespace rng = std::ranges;

Game_State_Menu::Game_State_Menu() : game_id{ Random_Number_Gen::g() }
{
    gb_interface.load_textures();

    ///TODO: Remove this magic constant
    state_buttons.reserve(2);

    state_buttons.push_back({ gb_interface.textures,B_N::Status::pause, {417,800}, "Pause" });
    state_buttons.push_back({ gb_interface.textures,B_N::Status::resume, {502,800}, "Resume" });

    game_id_t.setCharacterSize(26);
    game_id_t.setString(std::string{ "Game Id" }.append(11, ' ') + ": " + std::to_string(game_id));
    game_id_t.setPosition({ 0, 790 });
    game_id_t.setFillColor({ 236,203,180 });

    move.setCharacterSize(26);

    update();

    move.setPosition({ 0, 842 });
    move.setFillColor({ 236,203,180 });

    game_state.setCharacterSize(26);
    game_state.setPosition({ 0, 816 });
    game_state.setFillColor({ 236,203,180 });
}

auto Game_State_Menu::operator()(const rng::ref_view<std::deque<Card>> p, bool& pile_state) -> void
{
    if (move_count == Board::cards_pile * Board::total_piles)
    {
        Update_Game_State()(*this, Game_State::win, pile_state);
    }

    else if (const auto num_kings = rng::count_if(p, Lose_Condition()); num_kings == Board::cards_pile)
    {
        Update_Game_State()(*this, Game_State::lose, pile_state);
    }
}

auto Game_State_Menu::operator()(Game_State gs) & -> void
{
    ///TODO: Remove the l-value object test
    /// Remove the pile_State parameter from update_game_state function object
    /// lock the board another way
    bool test = false;
    Update_Game_State()(*this, gs, test);
}

auto Game_State_Menu::operator++() & -> const Game_State_Menu&
{
    ++move_count;
    update();
    return *this;
}

auto Game_State_Menu::click_listener(sf::Vector2f cursor_pos) & -> void
{
    Button_Interface<Game_State_Button>::click_listener(std::span{ state_buttons }, cursor_pos);
}

auto Game_State_Menu::release_listener(sf::Vector2f cursor_pos) & ->void
{
    Button_Interface<Game_State_Button>::release_listener(*this, cursor_pos);
}

void Game_State_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(game_id_t);
    target.draw(move);
    target.draw(game_state);
    target.draw(state_buttons.front());
    target.draw(state_buttons.back());
}

auto Game_State_Menu::Update_Game_State::operator()(Game_State_Menu& gsm, Game_State g_state, bool& pile_state) -> void
{
    gsm.state = g_state;
    pile_state = false;
    gsm.update();
}

auto Game_State_Menu::Lose_Condition::operator()(const Card& card)const ->bool
{
    return card.value() == Rank_Lib::Rank::king && card.position() == Card_State::face_up;
}

auto Game_State_Menu::update() & -> void
{
    switch (state)
    {
    case Game_State::playing:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Playing");
        move.setString(std::string{ "Move" }.append(15, ' ') + ": " + std::to_string(move_count));
        break;
    case Game_State::paused:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Paused");
        break;
    case Game_State::win:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Win");
        break;
    case Game_State::lose:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Lose");
        break;
    }
}