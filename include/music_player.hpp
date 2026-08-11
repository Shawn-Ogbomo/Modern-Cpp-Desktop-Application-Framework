#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "../include/util.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"

class Button : public sf::Drawable
{
	sf::Texture t;
public:
	friend class Music_Player;

	Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, int val, sf::Vector2f pos)
		:forms{ txtrs }
	{
		const auto bounds = std::pair<int, int>{ 0,5 };

		const auto& [lower_bound, upper_bound] = bounds;

		if (val < lower_bound || val > upper_bound)
		{
			throw std::out_of_range{ "No button name corresponding to value: " + std::to_string(val)};
		}

		name = static_cast<Button_Interface::ButtonName>(val);

		auto& [form_1, form_2, form_3] = forms;

		form_1.setPosition(pos);
		form_2.setPosition(pos);
		form_3.setPosition(pos);
	}

	auto operator()(Music_Player& mp) const-> void;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(std::get<0>(forms));
	}
private:
	std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{t,t,t};
	Button_Interface::ButtonName name{};
};

class  Music_Player : public sf::Drawable
{
	sf::Font font;
public:
	friend class Button;

	Music_Player();
	Music_Player(const Music_Player&) = delete;
	auto operator =(const Music_Player&) -> Music_Player & = delete;
	Music_Player(Music_Player&&) = delete;
	auto operator =(Music_Player&&) -> Music_Player & = delete;
	auto operator()(sf::RenderWindow& rw, sf::Vector2f cursor_pos = {}) ->void;
	operator bool() const { return static_cast<bool>(mode);};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	auto idle(Music_Player& mp) -> void;
	auto next() -> void { current_song = current_song < limit - 1 ? ++current_song : 0; };
	auto prev() -> void { current_song = current_song > 0 ? --current_song : current_song = limit - 1; };
	auto stop() -> void { songs[current_song].second.stop(); };
	auto pause() -> void { songs[current_song].second.pause(); };
	auto play() -> void { songs[current_song].second.play(); };

	sf::Text caption{ font };
	std::size_t limit{};
	std::size_t current_song{};
	std::vector<std::pair<sf::Text, sf::Music>> songs;
	std::vector<Button> buttons;
	Button_Manager bm;
	Button_Interface::ButtonMode mode{};
};

#endif // MUSIC_PLAYER.HPP