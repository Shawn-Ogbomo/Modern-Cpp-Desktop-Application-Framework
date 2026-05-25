#include "../headers/music_player.hpp"

Music_Player::Music_Player()
{
	for (const auto& song : std::filesystem::directory_iterator{ "..\\music" })
	{
		songs.push_back((sf::Music{ song }));
	}
	
	limit = songs.size();
}
