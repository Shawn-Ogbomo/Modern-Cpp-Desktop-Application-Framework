#include "../headers/util.hpp"

auto Util::check_stream(const std::istream& is, const std::string& message, const std::string& message2) -> void
{
	if (is.eof())
	{
		throw Terminate{ message + message2 };
	}

	if (is.fail())
	{
		throw std::invalid_argument{ message };
	}
}

auto Util::prev(int pos, std::array<std::vector<std::pair<Card, Rank_lib::Rank>>, Board::total_piles>& piles)
-> std::array < std::vector<std::pair<Card, Rank_lib::Rank>>, Board::total_piles>::iterator
{
	if (pos < 0 || pos > static_cast<int>(Rank_lib::Rank::queen))
	{
		throw std::out_of_range{ "Oops out of bounds...\n" };
	}

	if (!pos)
	{
		return piles.end();
	}

	return (piles.begin() + pos) - 1;
}