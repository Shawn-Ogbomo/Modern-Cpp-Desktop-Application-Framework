#ifndef   STATE_HPP
#define	 STATE_HPP

enum class ButtonState
{
	prev, pause, play, next, stop
};

inline auto operator++(ButtonState& b) ->ButtonState&
{
	return b = static_cast<int>(b) == static_cast<int>(ButtonState::stop) ?
		ButtonState::prev : static_cast<ButtonState>(static_cast<int>(b) + 1);
}

enum class Card_State
{
	face_down,
	face_up
};
#endif // STATE_HPP