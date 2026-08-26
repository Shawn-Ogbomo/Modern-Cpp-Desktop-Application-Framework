#include <filesystem>
#include <vector>

#include "../include/deck.hpp"
#include "../include/exceptions.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

namespace rng = std::ranges;

Deck::Deck()
{
    cm.load_textures();
    auto& [name, back_card] = cm.textures.front();
    cards.reserve(Board::total_piles * Board::cards_pile);

    rng::for_each(cm.textures.begin() + 1, cm.textures.end(), [&](auto& textures) {
        auto& [name, texture] = textures;
        cards.emplace_back(name.string(), texture, back_card); });
    shuffle();
}

auto Deck::shuffle() & -> void
{
    rng::shuffle(cards, Random_Number_Gen::g);
}

auto Deck::draw() & -> Card
{
    if (cards.empty())
    {
        throw Invalid_card_count{ "Insufficient cards...\n" };
    }

    auto last_card = cards.back();

    cards.pop_back();

    return last_card;
}