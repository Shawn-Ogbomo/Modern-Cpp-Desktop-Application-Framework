#include <filesystem>
#include <vector>

#include "../include/deck.hpp"
#include "../include/exceptions.hpp"
#include "../include/texture_manager.hpp"

namespace rng = std::ranges;

Deck::Deck(const Card_Manager& cm)
{
    auto& [name, back_card] = cm.textures().front();

    rng::for_each(cm.textures().begin() + 1, cm.textures().end(), [&](auto& textures) {
        auto& [name, texture] = textures;
        cards.emplace_back(name.string(), texture
            , back_card); }); [[likely]]

            shuffle();
}

auto Deck::shuffle() & -> void
{
    rng::shuffle(cards, Random_Number_Gen{}.generator());
}

auto Deck::draw() & -> Card
{
    if (cards.empty()) [[unlikely]]
    {
        throw Invalid_card_count{ "Insufficient cards...\n" };
    }

    auto last_card = std::move(cards.back());

    cards.pop_back();

    return last_card;
}