#include "../include/menu.hpp"

namespace B_N = Button_Names;
namespace rng = std::ranges;

using namespace std::literals;

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
    game_id_t.setString("Game Id"s.append(11, ' ') + ": " + std::to_string(game_id));

    move.setCharacterSize(26);

    move.setPosition({ 0, 842 });
    move.setFillColor({ 236,203,180 });
    move.setString("Move"s.append(15, ' ') + ": " + std::to_string(move_count));

    game_state.setCharacterSize(26);
    game_state.setPosition({ 0, 816 });
    game_state.setFillColor({ 236,203,180 });
    game_state.setString(get_labels().states.front());
}

auto Game_State_Menu::operator()(const rng::ref_view<std::deque<Card>> p) -> void
{
    if (move_count == Board::cards_pile * Board::total_piles)
    {
        Update_Game_State()(*this, Game_State::win);
    }

    else if (const auto num_kings = rng::count_if(p, Lose_Condition()); num_kings == Board::cards_pile)
    {
        Update_Game_State()(*this, Game_State::lose);
    }
}

auto Game_State_Menu::operator()(Game_State gs) & -> void
{
    Update_Game_State()(*this, gs);
}

auto Game_State_Menu::operator++() & -> const Game_State_Menu&
{
    ++move_count;
    move.setString("Move"s.append(15, ' ') + ": " + std::to_string(move_count));
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
    const auto& enable_components = [&]
        {
            Button_Interface<Media_Button>()(gsm.state_buttons.back());
            Button_Interface<Game_State_Button>()(gsm.state_buttons.back());
            gsm.enable_piles();
            gsm.c_sp->start();
        };

    const auto& disable_components = [&]
        {
            Button_Interface<Media_Button>()(gsm.state_buttons.front());
            gsm.disable_piles();
            gsm.c_sp->stop();
        };

    gsm.state = g_state;

    gsm.game_state.setString(gsm.get_labels().states[static_cast<int>(gsm.state)]);

    switch (gsm.state)
    {
    case Game_State::playing:
        enable_components();
        break;
    case Game_State::paused:
        disable_components();
        break;
    case Game_State::win:
    case Game_State::lose:
        disable_components();
        Button_Interface<Game_State_Button>()(gsm.state_buttons.front());
        break;
    }
}

auto Game_State_Menu::Lose_Condition::operator()(const Card& card)const ->bool
{
    return card.value() == Rank_Lib::Rank::king && card.position() == Card_State::face_up;
}

auto Game_State_Menu::enable_piles() & -> void
{
    std::get<0>(b_sp->piles[static_cast<int>(b_sp->pos_prev)]) = true;;
}

auto Game_State_Menu::disable_piles() & -> void
{
    std::get<0>(b_sp->piles[static_cast<int>(b_sp->pos_prev)]) = false;;
}