#include <utility>
#include <array>
#include <vector>
#include <fstream>
#include <filesystem>

#include "../include/util.hpp"
#include "../include/deck.hpp"
#include"../include/exceptions.hpp"
#include "../include/texture_manager.hpp"

using namespace Rank_Lib;

Deck::Deck()
{
    cm.load_textures();
    const auto& front_texture = cm.textures.front();

    for (auto index = 1; const auto& rank :ranks)
    {
        cards.emplace_back(Suit::hearts, rank, cm.textures[index++], front_texture);
        cards.emplace_back(Suit::diamonds, rank, cm.textures[index++], front_texture);
        cards.emplace_back(Suit::spades, rank, cm.textures[index++], front_texture);
        cards.emplace_back(Suit::clubs, rank, cm.textures[index++], front_texture);
    }

    shuffle();
}

auto Deck::draw() ->Card
{
	if (cards.empty())
	{
		throw Invalid_card_count{ "Insufficient cards...\n" };
	}

	auto last_card = std::move(cards.back());

	cards.pop_back();

	return last_card;
}