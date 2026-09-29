#include "../include/menu.hpp"

namespace B_N = Button_Names;
namespace rng = std::ranges;

Game_State_Menu::Game_State_Menu() : game_id{ Random_Number_Gen::g() }
{
    gb_interface.load_textures();

    constexpr auto limit = 2;

    state_buttons.reserve(limit);

    state_buttons.push_back({ gb_interface.textures,B_N::Status::pause, {417,800}, "Pause" });
    state_buttons.push_back({ gb_interface.textures,B_N::Status::resume, {502,800}, "Resume" });

    game_id_t.setCharacterSize(26);
    game_id_t.setPosition({ 0, 790 });
    game_id_t.setFillColor({ 236,203,180 });
    game_id_t.setString(std::string{ "Game Id" }.append(11, ' ') + ": " + std::to_string(game_id));

    move.setCharacterSize(26);

    move.setPosition({ 0, 842 });
    move.setFillColor({ 236,203,180 });
    move.setString(std::string{ "Move" }.append(15, ' ') + ": " + std::to_string(move_count));

    game_state.setCharacterSize(26);
    game_state.setPosition({ 0, 816 });
    game_state.setFillColor({ 236,203,180 });
    game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Playing");

}

auto Game_State_Menu::operator()(const rng::ref_view<std::deque<Card>> p, bool& pile_state) -> void
{
    if (move_count == Board::cards_pile * Board::total_piles)
    {
        Update_Game_State()(*this, Game_State::win);
        update();
    }

    else if (const auto num_kings = rng::count_if(p, Lose_Condition()); num_kings == Board::cards_pile)
    {
        Update_Game_State()(*this, Game_State::lose);
        update();
    }
}

auto Game_State_Menu::operator()(Game_State gs) & -> void
{
    Update_Game_State()(*this, gs);
}

auto Game_State_Menu::operator++() & -> const Game_State_Menu&
{
    ++move_count;
    move.setString(std::string{ "Move" }.append(15, ' ') + ": " + std::to_string(move_count));
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

auto Game_State_Menu::Update_Game_State::operator()(Game_State_Menu& gsm, Game_State g_state) -> void
{
    gsm.state = g_state;
    gsm.update();
}

auto Game_State_Menu::Lose_Condition::operator()(const Card& card)const ->bool
{
    return card.value() == Rank_Lib::Rank::king && card.position() == Card_State::face_up;
}

/// TODO: Make this an interface and lock the board here.
/// TODO: Manage the clock here as well so update_clock() in Time_Status doesn't run every frame
auto Game_State_Menu::update() & -> void
{
    switch (state)
    {
    case Game_State::playing:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Playing");
        Button_Interface<Media_Button>::operator()(state_buttons.back());
        break;
    case Game_State::paused:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Paused");
        Button_Interface<Media_Button>::operator()(state_buttons.front());
        break;
    case Game_State::win:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Win");
        Button_Interface<Game_State_Button>::operator()(state_buttons.front());
        break;
    case Game_State::lose:
        game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Lose");
        Button_Interface<Game_State_Button>::operator()(state_buttons.front());
        break;
    }
}