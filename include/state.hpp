#ifndef   STATE_HPP
#define	 STATE_HPP

namespace Button_Interface
{
    /// TODO: add pause, resume, restart, yes, and no.
    enum class ButtonName
    {
        prev, pause, play, next, stop, resume, restart, yes, no
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
    face_down, face_up
};

enum class Game_State
{
    playing, paused, win, lose
};

#endif // STATE_HPP