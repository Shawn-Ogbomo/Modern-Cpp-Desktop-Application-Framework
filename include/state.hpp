#ifndef   STATE_HPP
#define	 STATE_HPP

#include <variant>

namespace Button_Interface
{
	enum class ButtonName
	{
		prev, pause, play, next, stop
	};

	enum class ButtonState
	{
		idle, touched, pushed
	};

	template<class T>
	inline auto to_int(T b) -> int
	{
		return static_cast<int>(b);
	}
};

inline auto operator++(Button_Interface::ButtonName& b) ->Button_Interface::ButtonName&
{
	return b = static_cast<int>(b) == static_cast<int>(Button_Interface::ButtonName::stop) ?
		Button_Interface::ButtonName::prev : static_cast<Button_Interface::ButtonName>(static_cast<int>(b) + 1);
}

enum class Card_State
{
	face_down,
	face_up
};

enum class Texture_Manager_State
{
	cards, buttons = 53
};

#endif // STATE_HPP