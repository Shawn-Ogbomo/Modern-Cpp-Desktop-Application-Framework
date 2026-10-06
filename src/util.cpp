#include "../include/directory_manager.hpp"
#include "../include/util.hpp"

auto Util::load_font() -> const sf::Font&
{
    static const auto f = sf::Font{ Directory_Manager::assets_dir()
        / "fonts" / "galafera-med-font" / "GalaferaMediumItalic-JpXJK.ttf" };

    return f;
}

auto Util::delay_time(const sf::Clock& c, std::chrono::microseconds ms) -> void
{
    const auto t = c.getElapsedTime();
    auto          t2 = c.getElapsedTime();

    while (t2 < t + ms)
    {
        t2 = c.getElapsedTime();
    }
}

auto Util::local_time() -> std::string
{
    const auto time_now = std::chrono::zoned_time<std::chrono::system_clock::duration
        , const std::chrono::time_zone*>
    {
        std::chrono::current_zone(), // may throw
        std::chrono::system_clock::now()
    };

    return std::format("{:%a:%b:%d:%y %I:%M %p}", time_now.get_local_time());
}

auto Util::allocate(std::tuple<bool, std::deque<Card>, Rank_Lib::Rank, sf::Vector2f>& stack)
-> void
{
    auto& [state, card, rank, pos] = stack;
    std::ranges::fill_n(std::back_inserter(card), Board::cards_pile, Card{});

}