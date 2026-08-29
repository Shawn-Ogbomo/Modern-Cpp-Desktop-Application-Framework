#ifndef   STATE_HPP
#define	 STATE_HPP

namespace Button_Interface
{
    namespace Button_Names
    {
        enum class Media
        {
            prev, pause, play, next, stop
        };

        enum class Status
        {
             pause, resume
        };

        enum class General 
        {
            yes, no, ok, quit, hint, restart, leaderboards
        };
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