#include <numbers>
#include "../include/util.hpp"

using namespace std::numbers;

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

auto Util::position_card(sf::Sprite& front, sf::Sprite& back, Rank_lib::Rank rank, int v1, int v2) -> void
{
	 auto center_x  = 500.0f;
	 auto center_y  = 385.0f;
	 auto radius     = 300.0f;
	 auto pos_card = front.getLocalBounds().size;

	if (auto center = sf::Vector2f{ ((center_x * 2) - pos_card.x) / 2, ((center_y * 2) - pos_card.y) / 2 };
		rank == Rank_lib::Rank::king)
	{
		front.setPosition(center);
		back.setPosition(center);
		return;
	}

	sf::Angle a{ sf::radians(static_cast<float>(v1 * 2.0f * pi / (v2 - 1.0f) - (pi / 2.0f))) };

	auto a_radians = a.asRadians();
	auto pos = sf::Vector2f{ center_x + radius * std::cos(a_radians) - (pos_card.x / 2.0f), center_y + (radius * std::sin(a_radians)) - pos_card.y / 2.0f };

	front.setPosition(pos);
	back.setPosition(pos);
}