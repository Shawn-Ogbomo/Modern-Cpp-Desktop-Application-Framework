//#ifndef DASHBOARD_HPP
//#define DASHBOARD_HPP
//
//#include <string>
//#include <SFML/Audio.hpp>
//#include <SFML/Graphics/Text.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/Graphics/RectangleShape.hpp>
//
//class DashBoard : public sf::Drawable
//{
//	sf::Font font;
//	sf::Color font_color{ 255, 250, 250 };
//public:
//	explicit DashBoard(const Player& p);
//	DashBoard(const DashBoard&) = delete;
//	auto operator = (const DashBoard&)->DashBoard & = delete;
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
//private:
//	sf::Music song;
//	sf::Text song_name;
//
//	sf::Text game_id;
//	sf::Text move_count;
//
//	sf::Clock elapsed_time;*/
//	sf::RectangleShape dash;
//};
//
//#endif // !DASHBOARD_HPP