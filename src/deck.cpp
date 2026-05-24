#include <array>
#include <vector>
#include <fstream>
#include <utility>
#include <filesystem>
#include "../headers/deck.hpp"
#include "../headers/util.hpp"
#include"../headers/exceptions.hpp"
#include "../headers/texture_manager.hpp"

Deck::Deck()
{
	get_texture_manager().load_textures();

	const auto& textures = get_texture_manager().textures;
	auto index = 1;

	for (const auto& rank : Rank_lib::ranks)
	{
		cards.emplace_back(Suit::hearts, rank, textures[index++], textures[0]);
		cards.emplace_back(Suit::diamonds, rank, textures[index++], textures[0]);
		cards.emplace_back(Suit::spades, rank, textures[index++], textures[0]);
		cards.emplace_back(Suit::clubs, rank, textures[index++], textures[0]);
	}

	shuffle();
}

auto Deck::draw() ->Card
{
	if (cards.empty())
	{
		throw Invalid_card_count{ "Insufficient cards...\n" };
	}

	auto& last_card = std::move(cards.back());

	cards.pop_back();

	return last_card;
}