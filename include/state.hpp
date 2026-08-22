#ifndef   STATE_HPP
#define	 STATE_HPP

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

	enum class ButtonMode
	{
		off, on
	};
};

enum class Card_State
{
	face_down,face_up
};

enum class Game_State
{
	playing, paused, win, lose
};

#endif // STATE_HPP