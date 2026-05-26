#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

class Music_Player : public sf::Drawable
{
public:
	Music_Player();
	Music_Player(const Music_Player&) = delete;
	Music_Player(const Music_Player&&) = delete;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	auto song_name() -> std::string_view { return songs[current_song].first; };

	auto next() -> void { current_song = current_song < limit - 1 ? ++current_song : 0; };
	auto prev() -> void { current_song = current_song > 0 ? --current_song : current_song = limit - 1; };
	auto stop() -> void { songs[current_song].second.stop(); };
	auto pause() -> void { songs[current_song].second.pause(); };
	auto play() -> void { songs[current_song].second.play(); };
private:
	std::size_t limit{};
	std::size_t current_song{};
	std::vector<std::pair<std::string, sf::Music>> songs;
};

#endif //MUSIC_PLAYER.HPP