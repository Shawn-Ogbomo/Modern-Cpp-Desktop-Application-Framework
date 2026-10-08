#ifndef   STATE_HPP
#define	 STATE_HPP

#include <concepts>

namespace Button_Names
{
    enum class Media
    {
        prev, pause, play, next, stop = 4
    };

    enum class General
    {
        no, yes, ok, hint
    };

    enum class Game_State
    {
        paused, playing, win, lose, restart, quit
    };

        template<typename T>
        concept Is_Valid_Enum = std::is_enum_v<T>
            && (std::same_as<T, Button_Names::Media>
                || std::same_as<T, Game_State>
                || std::same_as<T, Button_Names::General>);

    inline auto operator++(Is_Valid_Enum auto& m) -> decltype(m)
    {
        const auto& last_button = [m] -> int {
            return (std::same_as<std::remove_reference<decltype(m)>::type, Media>) ?
                static_cast<int>(Media::stop) : static_cast<int>(General::hint);
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

#endif // STATE_HPP