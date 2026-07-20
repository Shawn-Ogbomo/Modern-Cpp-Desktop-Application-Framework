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
	auto t = c.getElapsedTime();
	auto t2 = c.getElapsedTime();
	
	while (t2 < t + ms)
	{
		t2 = c.getElapsedTime();
	}
}

auto Util::allocate(std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>& stack) -> void
{
	auto& [state, cards] = stack;
	std::fill_n(std::back_inserter(cards), 4, std::pair{ Card{},Rank_lib::Rank{} });
}