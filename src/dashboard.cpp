#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

#include "../headers/dashboard.hpp"
#include "../headers/exceptions.hpp"
#include"../headers/random_number_gen.hpp"

DashBoard::DashBoard()
{
	if (!font.openFromFile("../../../../fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"))
	{
		throw Invalid_file{ "The file does not exist...\n" };
	}

	//if (!song.openFromFile("music\\Invitation.wav"))
	//{
	//	throw Invalid_file{ "The music file does not exist...\n" };
	//}

	dash.setFillColor(sf::Color{ 228, 193, 156 });
	dash.setOrigin(sf::Vector2f{ 0.f,0.f });
	dash.setPosition(sf::Vector2f{ 0.f,700.f });

	//song_name.setFont(font);
	//song_name.setString("Song name: Ray Bryant Invitation");
	//song_name.setCharacterSize(30);
	//song_name.setFillColor(font_color);
	//song_name.setPosition(sf::Vector2f{ 0, 588 });

	move_count.setFont(font);
	move_count.setString("Move: " + std::to_string(0));
	move_count.setPosition(sf::Vector2f{ 0,500 });
	move_count.setFillColor(font_color);

	game_id.setFont(font);
	game_id.setString("Game Id: #" + std::to_string(Random_Number_Gen::g()));
	game_id.setPosition(sf::Vector2f{ 0,740 });
	//game_id.setCharacterSize(30);
	game_id.setFillColor(font_color);

	state.setFont(font);
	state.setString("State: Playing");
	state.setPosition(sf::Vector2f{ 0,710 });
	state.setFillColor(font_color);
	//song.setVolume(0);
	//song.setLoop(true);
	//song.play();

	/*song_status.setFont(font);
	song_status.setString("Playing!");
	song_status.setCharacterSize(30);
	song_status.setFillColor(font_color);
	song_status.setPosition(0, 630);*/
}

void DashBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dash);
	target.draw(game_id);
	target.draw(move_count);
	target.draw(state);
	target.draw(date);
	//target.draw(song_name);
}