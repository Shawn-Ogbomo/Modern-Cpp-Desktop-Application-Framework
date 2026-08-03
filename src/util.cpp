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
	const auto t = c.getElapsedTime();
	auto t2 = c.getElapsedTime();

	while (t2 < t + ms)
	{
		t2 = c.getElapsedTime();
	}
}

auto Util::allocate(std::pair<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>>& stack) -> void
{
	auto& [state, cards] = stack;
	std::ranges::fill_n(std::back_inserter(cards), Board::cards_pile, std::pair{Card{},Rank_Lib::Rank{}});
}

auto Util::position_card(sf::Sprite& front, sf::Sprite& back, Rank_Lib::Rank rank, int v1, int v2) -> void
{
	const auto center_x = 500.0f;
	const auto center_y = 385.0f;
	const auto radius = 300.0f;
	const auto pos_card = front.getLocalBounds().size;

	if (const auto center = sf::Vector2f{ ((center_x * 2) - pos_card.x) / 2, ((center_y * 2) - pos_card.y) / 2 };
		rank == Rank_Lib::Rank::king)
	{
		front.setPosition(center);
		back.setPosition(center);
		return;
	}

	const auto a = sf::Angle{ sf::radians(static_cast<float>(v1 * 2.0f * pi / (v2 - 1.0f) - (pi / 2.0f))) };

	auto a_radians = a.asRadians();
	auto pos = sf::Vector2f{ center_x + radius * std::cos(a_radians) - (pos_card.x / 2.0f), center_y + (radius * std::sin(a_radians)) - pos_card.y / 2.0f };

	front.setPosition(pos);
	back.setPosition(pos);
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