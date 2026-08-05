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
namespace fs = std::filesystem;

Deck::Deck()
{
	fs::current_path("../../../../assets/");

	cm.load_textures();
	auto& [name, back_card] = cm.textures.front();
	cards.reserve(Board::total_piles * Board::cards_pile);

	std::for_each(cm.textures.begin() + 1, cm.textures.end(), [&](auto& textures) {
		auto& [name, texture] = textures;
		cards.emplace_back(name.string(), texture, back_card); });

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