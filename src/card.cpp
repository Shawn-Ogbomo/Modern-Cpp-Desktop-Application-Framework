#include <map>
#include <format>
#include <iostream>

#include "../include/suit.hpp"
#include "../include/card.hpp"

namespace fs = std::filesystem;

Card::Card(std::string_view card_name, sf::Texture& f,  sf::Texture& re, Card_State st)
	:face{f},
	reverse{re},
	state{ st } {

	const auto pos_suite_name_begin = (card_name.find_first_of("-") + 1);
	const auto count = (card_name.find_last_of("-") - 1) - (pos_suite_name_begin)+1;

	suit = suits.find(card_name.substr(pos_suite_name_begin, count))->second;
	rank = 
	//extract the integral value in the string and cast it to a Rank
		//use std::format...
}