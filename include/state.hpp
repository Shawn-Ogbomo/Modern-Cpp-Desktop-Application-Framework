#ifndef   STATE_HPP
#define	 STATE_HPP

#include <concepts>
#include <type_traits>

namespace Button_Names
{
    enum class Media
    {
        prev, pause, play, next, stop
    };

    enum class Confirm
    {
        no, yes
    };

    enum class Confirm_Input
    {
        cancel, ok
    };

    enum class Exit
    {
        restart, quit
    };

    enum class General
    {
        ok, up, down
    };

    enum class Game_State
    {
        paused, playing, win, lose
    };

    inline auto buttons(std::string_view sv1, std::string_view sv2)
        -> std::unordered_map<std::string_view, float>
    {
        const auto confirm_button_pos = std::unordered_map<std::string_view, float>
        {
            { sv1,502.0f },{ sv2,417.0f }
        };

        return confirm_button_pos;
    }

    template<typename T>
    concept Is_Valid_Enum = std::is_enum_v<T>
        && (std::same_as<T, Button_Names::Media>
            || std::same_as<T, Game_State>
            || std::same_as<T, Button_Names::General>
            || std::same_as<T, Button_Names::Confirm>
            || std::same_as<T, Button_Names::Exit>
            || std::same_as<T, Button_Names::Confirm_Input>);

    inline auto operator++(Is_Valid_Enum auto& m) -> decltype(m)
    {
        using m_non_ref = std::remove_cvref_t<decltype(m)>;

        const auto& last_button = [m] -> int {
            return (std::same_as<m_non_ref, Media>) ?
                static_cast<int>(Media::stop) : static_cast<int>(General::down);
            };

        return m = (m == static_cast<m_non_ref> (last_button())
            ? static_cast<m_non_ref>(0)
            : static_cast<m_non_ref>(static_cast<int>(m) + 1));
    }
};

enum class ButtonMode
{
    off, on
};

enum class Card_State
{
    face_down, face_up
};

struct State_Label
{
    std::array <std::string, 4> states{
        std::format("State{:>17}{:>7}" , ':' ,"Paused"),
        std::format("State{:>17}{:>8}" , ':' ,"Playing"),
        std::format("State{:>17}{:>4}" , ':' ,"Win"),
        std::format("State{:>17}{:>5}" , ':' ,"Lose")
    };
};

inline auto get_labels() -> const State_Label&
{
    static const auto labels = State_Label{};
    return labels;
}

#endif // STATE_HPP