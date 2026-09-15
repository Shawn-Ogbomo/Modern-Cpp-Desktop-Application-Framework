#ifndef   STATE_HPP
#define	 STATE_HPP

namespace Button_Names
{
    enum class Media
    {
        prev, pause, play, next, stop = 4
    };

    /// TODO: Finish template this operator.
    /// TODO: Write a concept to make this operator exclusive to enums in Button_Interface::Button_Names
    /// Read CPP ref RTTI Type_Id
    inline auto operator++(auto& m) -> decltype(m)
    {
        return m = (m == Media::stop ? static_cast<std::remove_reference<decltype(m)>::type>(0)
            : static_cast<std::remove_reference<decltype(m)>::type>(static_cast<int>(m) + 1));
    }

    enum class Status
    {
        pause, resume = 1
    };

    enum class General
    {
        yes, no, ok, quit, hint, restart, leaderboards = 6
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

enum class Card_State
{
    face_down, face_up
};

enum class Game_State
{
    playing, paused, win, lose
};

#endif // STATE_HPP