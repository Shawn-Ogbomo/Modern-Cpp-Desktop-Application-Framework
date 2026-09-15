#ifndef   STATE_HPP
#define	 STATE_HPP

#include <iostream>

namespace Button_Names
{
    enum class Media
    {
        prev, pause, play, next, stop = 4
    };

    enum class Status
    {
        pause, resume = 1
    };

    enum class General
    {
        yes, no, ok, quit, hint, restart = 5
    };

    /// TODO: Write a concept to make this operator exclusive to enums in Button_Interface::Button_Names
    inline auto operator++(auto& m) -> decltype(m)
    {
        const auto& t = [m] -> int {
            if (typeid(m) == typeid(Media))
            {
                return static_cast<int>(Media::stop);
            }

            else if (typeid(m) == typeid(Status))
            {
                return static_cast<int>(Status::resume);
            }

            else if (typeid(m) == typeid(General))
            {
                return static_cast<int>(General::restart);
            }

            throw std::invalid_argument{ "Button_Names::operator ++ (auto& m) The target object is of an invalid type.\n" };
            };

        return m = (m == static_cast<std::remove_reference<decltype(m)>::type>(t())
            ? static_cast<std::remove_reference<decltype(m)>::type>(0)
            : static_cast<std::remove_reference<decltype(m)>::type>(static_cast<int>(m) + 1));
    }
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