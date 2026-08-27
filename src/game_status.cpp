#include <SFML/Graphics.hpp>

#include "../include/directory_manager.hpp"
#include "../include/game_status.hpp"
#include "../include/util.hpp"

namespace rng = std::ranges;

Game_Status::Game_Status() : game_id{ Random_Number_Gen::g() }
{
    Util::load_font(std::filesystem::path{ Directory_Manager::assets_dir()
        / "fonts"/"galafera-med-font"/"GalaferaMediumItalic-JpXJK.ttf" }, font);

    game_id_t.setFont(font);
    game_id_t.setCharacterSize(26);
    game_id_t.setString(std::string{ "Game Id" }.append(11, ' ') + ": " + std::to_string(game_id));
    game_id_t.setPosition({ 0, 790 });
    game_id_t.setFillColor({ 236,203,180 });

    move.setFont(font);
    move.setCharacterSize(26);

    update();

    move.setPosition({ 0, 842 });
    move.setFillColor({ 236,203,180 });

    game_state.setFont(font);
    game_state.setCharacterSize(26);
    game_state.setPosition({ 0, 816 });
    game_state.setFillColor({ 236,203,180 });
}

auto Game_Status::update() & -> void
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

auto Game_Status::Update_Game_State::operator()(Game_Status& gs, Game_State g_state
    , bool& pile_state) -> void
{
    gs.state = g_state;
    pile_state = false;
    gs.update();
}

auto Game_Status::Lose_Condition::operator()(Card card)const ->bool
{
    return card.value() == Rank_Lib::Rank::king && card.position() == Card_State::face_up;
}

auto Game_Status::operator()(const std::deque<Card>& p, bool& pile_state) -> void
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

auto Game_Status::operator++() & -> const Game_Status&
{
    ++move_count;
    update();
    return *this;
}

void Game_Status::draw(sf::RenderTarget& target,
    sf::RenderStates states) const
{
    target.draw(game_id_t);
    target.draw(move);
    target.draw(game_state);
}