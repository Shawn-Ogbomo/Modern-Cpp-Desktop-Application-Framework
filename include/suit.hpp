#ifndef  SUIT_HPP
#define  SUIT_HPP

#include <map>

enum class Suit
{
	diamonds,
	hearts,
	spades,
	clubs
};

inline std::map<std::string_view, Suit> suits{
	{"hearts", Suit::hearts}, { "diamonds",Suit::diamonds },
	{ "spades",Suit::spades }, { "clubs",Suit::clubs } };

#endif // SUIT_HPP