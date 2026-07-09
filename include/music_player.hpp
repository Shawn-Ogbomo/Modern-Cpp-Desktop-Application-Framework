#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "../include/state.hpp"
#include "../include/button.hpp"

class  Music_Player : public sf::Drawable
{
	sf::Font font{ };
public:
	Music_Player();
	Music_Player(const Music_Player&) = delete;
	auto operator =(const Music_Player&) -> Music_Player& = delete;
	Music_Player(const Music_Player&&) = delete;
	auto operator =(const Music_Player&&) -> Music_Player & = delete;
	auto operator()(const sf::Clock& c, sf::RenderWindow& rw, sf::Vector2f cursor_pos = {}) ->void;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	friend auto idle(Music_Player&mp) -> void;

	auto next() -> void { current_song = current_song < limit - 1 ? ++current_song : 0; };
	auto prev() -> void { current_song = current_song > 0 ? --current_song : current_song = limit - 1; };
	auto stop() -> void { songs[current_song].second.stop(); };
	auto pause() -> void { songs[current_song].second.pause(); };
	auto play() -> void { songs[current_song].second.play(); };
private:	
	sf::Text caption{ font };
	std::size_t limit{};
	std::size_t current_song{};
	std::vector<std::pair<sf::Text, sf::Music>> songs;
	std::vector<Button> buttons;
};

#endif // MUSIC_PLAYER.HPP