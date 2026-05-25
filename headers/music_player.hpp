#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>

#include <vector>
#include <iostream>

class Music_Player
{
public:
	Music_Player();
	Music_Player(const Music_Player&) = delete;
	Music_Player(const Music_Player&&) = delete;

	auto next() -> void { current_song = current_song < limit - 1 ? ++current_song : 0; };
	auto prev() -> void { current_song = current_song > 0 ? --current_song : current_song = limit - 1; };
	auto stop() -> void { songs[current_song].stop(); };
	auto pause() -> void { songs[current_song].pause(); };
	auto play() -> void { songs[current_song].play(); };
private:
	std::size_t limit{};
	std::size_t current_song{};
	std::vector<sf::Music> songs;

};

#endif //MUSIC_PLAYER.HPP