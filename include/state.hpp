#ifndef   STATE_HPP
#define	 STATE_HPP

#include <concepts>

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

    template<typename T>
    concept Is_Valid_Enum = std::is_enum_v<T>
        && (std::same_as<T, Media>
            || std::same_as<T, Status>
            || std::same_as<T, General>);

    inline auto operator++(Is_Valid_Enum auto& m) -> decltype(m)
    {
        const auto& last_button = [m]() -> int {
            if (std::is_same_v<std::remove_reference<decltype(m)>, Media >)
            {
                return static_cast<int>(Media::stop);
            }

            else if (std::is_same_v<std::remove_reference<decltype(m)>, Status >)
            {
                return static_cast<int>(Status::resume);
            }

            return static_cast<int>(General::restart);
            };

        return m = (m == static_cast<std::remove_reference<decltype(m)>::type>(last_button())
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