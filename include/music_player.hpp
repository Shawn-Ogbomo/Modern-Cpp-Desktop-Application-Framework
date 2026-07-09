#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "../include/state.hpp"

class Button : public sf::Drawable
{
public:
	friend class Music_Player;
	
	explicit Button(const sf::Texture& t, const sf::Texture& t2, const sf::Texture& t3)
	{
		static auto bs = ButtonState{};
		name = bs;
		++bs;

		forms.push_back(std::move(sf::Sprite{ t }));
		forms.push_back(std::move(sf::Sprite{ t2 }));
		forms.push_back(std::move(sf::Sprite{ t3 }));
	}

	auto operator()(Music_Player& mp) -> void;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(forms[0]);
	}

private:
	ButtonState name{};
	std::vector<sf::Sprite>forms;
};

class  Music_Player : public sf::Drawable
{
	sf::Font font{ };
public:
	friend class Button;

	Music_Player();
	Music_Player(const Music_Player&) = delete;
	auto operator =(const Music_Player&) -> Music_Player& = delete;
	Music_Player(const Music_Player&&) = delete;
	auto operator =(const Music_Player&&) -> Music_Player & = delete;
	auto operator()(const sf::Clock& c, sf::RenderWindow& rw, sf::Vector2f cursor_pos = {}) ->void;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:	
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
};

#endif // MUSIC_PLAYER.HPP