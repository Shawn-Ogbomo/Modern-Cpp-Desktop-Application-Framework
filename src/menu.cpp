#include "../include/menu.hpp"

namespace B_N = Button_Names;
namespace rng = std::ranges;

using namespace std::literals;

Game_State_Menu::Game_State_Menu(const General_Buttons& gb) : game_id{ Random_Number_Gen::g() }
{
    state_buttons.reserve(Menu::limit);

    state_buttons.push_back({ gb.textures,B_N::Game_State::paused, {417,800}, "Pause" });
    state_buttons.push_back({ gb.textures,B_N::Game_State::playing, {502,800}, "Resume" });

    game_id_t.setCharacterSize(26);
    game_id_t.setPosition({ 0, 790 });
    game_id_t.setFillColor({ 236,203,180 });
    game_id_t.setString("Game Id"s.append(11, ' ') + ": " + std::to_string(game_id));

    move.setCharacterSize(26);

    move.setPosition({ 0, 842 });
    move.setFillColor({ 236,203,180 });
    move.setString("Move"s.append(15, ' ') + ": " + std::to_string(move_count));

    state = B_N::Game_State::playing;

    game_state.setCharacterSize(26);
    game_state.setPosition({ 0, 816 });
    game_state.setFillColor({ 236,203,180 });
    game_state.setString(get_labels().states[static_cast<int>(state)]);
}

auto Game_State_Menu::operator()(const rng::ref_view<std::deque<Card>> p, Refs_Components& r_c) -> void
{
    if (move_count == Board::cards_pile * Board::total_piles)
    {
        update_game_state(B_N::Game_State::win, r_c);
    }

    else if (const auto num_kings = rng::count_if(p, Lose_Condition()); num_kings == Board::cards_pile)
    {
        update_game_state(B_N::Game_State::lose, r_c);
    }
}

auto Game_State_Menu::operator++() & -> const Game_State_Menu&
{
    ++move_count;
    move.setString("Move"s.append(15, ' ') + ": " + std::to_string(move_count));
    return *this;
}

void Game_State_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(game_id_t);
    target.draw(move);
    target.draw(game_state);
    target.draw(state_buttons.front());
    target.draw(state_buttons.back());
}

auto Game_State_Menu::update_game_state(B_N::Game_State g_state, Refs_Components& r_c) & -> void
{
    const auto& disable_piles = [&, this]
        {
            std::get<0>(r_c.sp2_b.front().piles[static_cast<int>(r_c.sp2_b.front().pos_prev)]) = false;
        };

    const auto& enable_piles = [&, this]
        {
            std::get<0>(r_c.sp2_b.front().piles[static_cast<int>(r_c.sp2_b.front().pos_prev)]) = true;
        };

    const auto& enable_components = [&, this]
        {
            enable_piles();
            r_c.sp1_c.front().start();
            r_c.sp5_gsm.front().mode = ButtonMode::on;
            r_c.sp4_mp.front().mode = ButtonMode::on;
        };

    const auto& disable_components = [&, this]
        {
            disable_piles();
            r_c.sp1_c.front().stop();
            r_c.sp4_mp.front().mode = ButtonMode::off;
        };

    state = g_state;

    game_state.setString(get_labels()
        .states[static_cast<int>(state)]);

    switch (state)
    {
    case B_N::Game_State::playing:
    case B_N::Game_State::restart:
        enable_components();
        break;
    case B_N::Game_State::paused:
        disable_components();
        break;
    case B_N::Game_State::win:
    case B_N::Game_State::lose:
        disable_components();
        r_c.sp5_gsm.front().mode = ButtonMode::off;
        break;
    case B_N::Game_State::quit:
        disable_components();
        r_c.sp3_b.front() = false;
        r_c.sp7_rw.front().close();
        break;
    }
}

auto Game_State_Menu::Lose_Condition::operator()(const Card& card)const ->bool
{
    return card.value() == Rank_Lib::Rank::king && card.position() == Card_State::face_up;
}

Exit_Menu::Exit_Menu(const General_Buttons& gb)
{
    buttons.reserve(Menu::limit);

    buttons.push_back({ gb.textures, B_N::Game_State::restart, {5, 0}, "Reset" });
    buttons.push_back({ gb.textures, B_N::Game_State::quit, {5, 40}, "Quit" });
}

void Exit_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(buttons.front());
    target.draw(buttons.back());
}