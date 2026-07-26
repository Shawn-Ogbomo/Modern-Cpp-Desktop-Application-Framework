#include <utility>
#include <array>
#include <vector>
#include <fstream>
#include <filesystem>

#include "../include/util.hpp"
#include "../include/deck.hpp"
#include"../include/exceptions.hpp"
#include "../include/texture_manager.hpp"

Deck::Deck()
{
	const auto& textures = get_texture_manager().textures;
	const auto& front_texture = textures.front();

	for (auto index = static_cast<int>(Texture_Manager_State::cards); const auto& rank : Rank_lib::ranks)
	{
		cards.emplace_back(Suit::hearts, rank, textures[index++], front_texture);
		cards.emplace_back(Suit::diamonds, rank, textures[index++], front_texture);
		cards.emplace_back(Suit::spades, rank, textures[index++], front_texture);
		cards.emplace_back(Suit::clubs, rank, textures[index++], front_texture);
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