#include "../include/util.hpp"

auto Util::check_stream(const std::istream& is, const std::filesystem::path& p, const std::string& message, const std::string& message2) -> void
{
	if (is.eof())
	{
		throw Terminate{ message + message2 };
	}

	if (is.fail())
	{
		throw std::invalid_argument{ std::filesystem::absolute(p).string() + message };
	}
}

auto Util::load_font(const std::filesystem::path& p, sf::Font& f) ->void
{
	if (!f.openFromFile(p.string()))
	{
		throw Invalid_file{ "Invalid file: " + p.string() + "\n" };
	}
}

auto Util::delay_time(const sf::Clock& c, std::chrono::microseconds ms)-> void
{
	const auto t = c.getElapsedTime();
	auto t2 = c.getElapsedTime();

	while (t2 < t + ms)
	{
		t2 = c.getElapsedTime();
	}
}

auto::Util::local_time()->std::string
{
	const auto time_now = std::chrono::zoned_time<std::chrono::system_clock::duration, const std::chrono::time_zone*>
	{
		std::chrono::current_zone(), // may throw
		std::chrono::system_clock::now()
	};

	return std::format("{:%a:%b:%d:%y %I:%M %p}", time_now.get_local_time());
}

auto::Util::allocate(std::tuple<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>, sf::Vector2f>& stack) -> void
{
	auto& [state, cards, pos] = stack;
	std::ranges::fill_n(std::back_inserter(cards), Board::cards_pile, std::pair{ Card{},Rank_Lib::Rank{} });
}