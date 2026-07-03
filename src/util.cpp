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

auto Util::delay_time(const sf::Clock& c, std::chrono::seconds s) -> void
{
	auto t{ c.getElapsedTime() };

	while (t.asSeconds() < (t.asSeconds() + s.count()))
	{
		t = c.getElapsedTime();
		std::cout << t.asSeconds() << "\n";
	}
}