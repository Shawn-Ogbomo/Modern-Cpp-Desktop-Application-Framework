#include "../include/menu.hpp"

namespace B_N = Button_Names;
namespace rng = std::ranges;

using namespace std::literals;

Game_State_Menu::Game_State_Menu(const General_Buttons& gb)
{
    Random_Number_Gen rng{ 100000,999999 };
    game_id = rng.dst(rng.g);

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

/// TODO: split this into two functions
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
            r_c.sp3_c.front().start();
            r_c.sp4_em.front().mode = ButtonMode::on;
            r_c.sp7_gsm.front().mode = ButtonMode::on;
            r_c.sp5_mp.front().mode = ButtonMode::on;
        };

    const auto& disable_components = [&, this]
        {
            disable_piles();
            r_c.sp3_c.front().stop();
            r_c.sp5_mp.front().mode = ButtonMode::off;
        };

    state_prev = state;
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
        r_c.sp7_gsm.front().mode = ButtonMode::on;
        r_c.sp4_em.front().mode = ButtonMode::on;
        break;
    case B_N::Game_State::win:
        disable_components();
        r_c.sp8_cm.front().prompt.setString(r_c.sp8_cm.front()
            .get_prompts().labels.back());

        r_c.sp7_gsm.front().mode = ButtonMode::off;
        r_c.sp4_em.front().mode = ButtonMode::on;
        r_c.sp8_cm.front().mode = ButtonMode::on;
        break;
    case B_N::Game_State::lose:
        disable_components();
        r_c.sp7_gsm.front().mode = ButtonMode::off;
        r_c.sp4_em.front().mode = ButtonMode::on;
        break;
    case B_N::Game_State::quit:
        disable_components();
        r_c.sp8_cm.front().prompt.setString(r_c.sp8_cm.front()
            .get_prompts().labels.front());
        r_c.sp4_em.front().mode = ButtonMode::off;
        r_c.sp7_gsm.front().mode = ButtonMode::off;
        r_c.sp8_cm.front().mode = ButtonMode::on;
        break;
    }
}

auto Game_State_Menu::Lose_Condition::operator()(const Card& card)const ->bool
{
    return card.value().front() == Rank_Lib::Rank::king &&
        card.position().front() == Card_State::face_up;
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

Confirmation_Menu::Confirmation_Menu(const General_Buttons& gb, const Text_Boxes& tb,
    std::span<const sf::RenderWindow>rws) : text_box{ tb.t }
{
    prompt.setString(get_prompts().labels.front());

    buttons.reserve(Menu::limit);

    prompt.setFillColor({ 236,203,180 });
    prompt.setCharacterSize(26);

    const auto dimensions_window = static_cast<sf::Vector2f>(rws.front().getSize());
    const auto dimensions_textbox = sf::Vector2f{ text_box.getGlobalBounds().size };
    const auto dimensions_prompt = prompt.getGlobalBounds().size;

    prompt.setPosition({ ((dimensions_window.x - dimensions_textbox.x) / 2) + (dimensions_textbox.x / 2)
        - (dimensions_prompt.x / 2) , ((dimensions_window.y - dimensions_textbox.y) / 2)
        + (dimensions_textbox.y / 2) - dimensions_prompt.y });

    text_box.setPosition({ (dimensions_window.x - dimensions_textbox.x) / 2
        , (dimensions_window.y - dimensions_textbox.y) / 2 });

    buttons.push_back({ gb.textures, B_N::General::yes, {417, text_box.getGlobalBounds().position.y
        + dimensions_textbox.y - 50}, "Yes" });

    buttons.push_back({ gb.textures, B_N::General::no, {502,  text_box.getGlobalBounds().position.y
        + dimensions_textbox.y - 50}, "No" });
}

void Confirmation_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mode == ButtonMode::on)
    {
        target.draw(text_box);
        target.draw(prompt);
        target.draw(buttons.front());
        target.draw(buttons.back());
    }
}

auto Confirmation_Menu::test(Refs_Components& r_c) & ->void
{
    if (cbs.front().name == Button_Names::General::yes)
    {
        r_c.sp1_b.front() = false;
        r_c.sp6_rw.front().close();
        return;
    }

    r_c.sp7_gsm.front().update_game_state(r_c.sp7_gsm.front().state_prev, r_c);
    r_c.sp8_cm.front().mode = ButtonMode::off;
}