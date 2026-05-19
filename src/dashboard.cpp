//#include <SFML/Graphics/Transformable.hpp>
//
//#include "../headers/dashboard.hpp"
//#include "../headers/exceptions.hpp"
//#include"../headers/random_number_gen.hpp"
//
//DashBoard::DashBoard()
//{
//	if (!font.loadFromFile("fonts\\pixel_letters\\Pixellettersfull-BnJ5.ttf"))
//	{
//		throw Invalid_file{ "The file does not exist...\n" };
//	}
//
//	/*if (!song.openFromFile("music\\Invitation.wav"))
//	{
//		throw invalid_file{ "The music file does not exist...\n" };
//	}*/
//
//	/*dash.setOrigin(500, 50);
//	dash.setPosition(500, 650);
//	dash.setFillColor(sf::Color(128, 126, 120));*/
//
//	/*name.setFont(font);
//	name.setString(p.name);
//	name.setCharacterSize(30);
//	name.setFillColor(font_color);
//	name.setPosition(500, 588);
//
//	age.setFont(font);
//	age.setString(std::to_string(p.age));
//	age.setCharacterSize(30);
//	age.setFillColor(font_color);
//	age.setPosition(500, 625);
//
//	sex.setFont(font);
//	sex.setString(p.sex);
//	sex.setCharacterSize(30);
//	sex.setFillColor(font_color);
//	sex.setPosition(500, 662);
//
//	song_name.setFont(font);
//	song_name.setString("Song name: Ray Bryant Invitation");
//	song_name.setCharacterSize(30);
//	song_name.setFillColor(font_color);
//	song_name.setPosition(0, 588);
//
//	game_id.setFont(font);
//
//	game_id.setString("#" + std::to_string(Random_Number_Gen::distrib(Random_Number_Gen::rd)));
//
//	game_id.setCharacterSize(30);
//	game_id.setFillColor(font_color);
//	game_id.setPosition(940, 662);
//
//	song.setVolume(0);
//	song.setLoop(true);S
//	song.play();
//
//	song_status.setFont(font);
//	song_status.setString("Playing!");
//	song_status.setCharacterSize(30);
//	song_status.setFillColor(font_color);
//	song_status.setPosition(0, 630);*/
//}
//
//void DashBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	//target.draw(dash);
//	//target.draw(sex);
//	//target.draw(game_id);
//	//target.draw(song_name);
//}