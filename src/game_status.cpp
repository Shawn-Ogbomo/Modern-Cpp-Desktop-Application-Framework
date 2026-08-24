#include <SFML/Graphics.hpp>

#include "../include/directory_manager.hpp"
#include "../include/exceptions.hpp"
#include "../include/game_status.hpp"
#include "../include/util.hpp"

namespace rng = std::ranges;

Game_Status::Game_Status() : game_id{ Random_Number_Gen::g() }
{
    Util::load_font(std::filesystem::path{ Directory_Manager::assets_dir()
        / "fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf" }, font);

    game_id_t.setFont(font);
    game_id_t.setCharacterSize(26);
    game_id_t.setString(std::string{ "Game Id" }.append(11, ' ') + ": " + std::to_string(game_id));
    game_id_t.setPosition(sf::Vector2f{ 0, 790 });
    game_id_t.setFillColor(sf::Color{ 63, 59, 147 });

    move.setFont(font);
    move.setCharacterSize(26);

    update();

    move.setPosition(sf::Vector2f{ 0, 842 });
    move.setFillColor(sf::Color{ 63, 59, 147 });

    game_state.setFont(font);
    game_state.setCharacterSize(26);
    game_state.setPosition(sf::Vector2f{ 0, 816 });
    game_state.setFillColor(sf::Color{ 63, 59, 147 });
}

auto::Game_Status::update() -> void
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

auto::Game_Status::operator()(const std::deque<Card>& p, bool& pile_state)-> void
{
    const auto& lose_condition = [](auto c) -> int {
        return c.value() == Rank_Lib::Rank::king && c.position() == Card_State::face_up;
        };

    if (move_count == Board::cards_pile * Board::total_piles)
    {
        state = Game_State::win;
        pile_state = false;
        update();
    }

    else if (auto num_kings = rng::count_if(p, lose_condition); num_kings == Board::cards_pile)
    {
        state = Game_State::lose;
        pile_state = false;
        update();
    }
}

auto::Game_Status::operator++() -> const Game_Status&
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