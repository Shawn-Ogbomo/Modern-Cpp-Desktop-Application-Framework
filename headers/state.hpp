#ifndef  STATE_HPP
#define	 STATE_HPP

namespace State_lib
{
	enum class Card_State
	{
		face_down,
		face_up
	};

	enum class Game_state
	{
		playing,
		paused
	};
}
#endif //STATE_HPP