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
        no, yes, ok
    };

    enum class Exit
    {
        restart, quit
    };

    enum class General
    {
        ok, up, down, hint
    };

    enum class Game_State
    {
        paused, playing, win, lose
    };

    const auto confirm_button_pos = std::unordered_map<std::string, float>
    {
        { "Yes",417.0f },{ "No",502.0f },{ "OK", (587.0f / 2.0f) - 42.5f }
    };

    template<typename T>
    concept Is_Valid_Enum = std::is_enum_v<T>
        && (std::same_as<T, Button_Names::Media>
            || std::same_as<T, Game_State>
            || std::same_as<T, Button_Names::General>
            || std::same_as<T, Button_Names::Confirm>
            || std::same_as<T, Button_Names::Exit>);

    inline auto operator++(Is_Valid_Enum auto& m) -> decltype(m)
    {
        using m_non_ref = std::remove_cvref_t<decltype(m)>;

        const auto& last_button = [m] -> int {
            return (std::same_as<m_non_ref, Media>) ?
                static_cast<int>(Media::stop) : static_cast<int>(General::hint);
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