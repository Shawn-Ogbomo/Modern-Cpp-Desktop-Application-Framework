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

    enum class General
    {
        no, yes, ok, up, down, hint
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
    std::array <std::string, 6> states{
        std::format("State{:>17}{:>7}" , ':' ,"Paused"),
        std::format("State{:>17}{:>8}" , ':' ,"Playing"),
        std::format("State{:>17}{:>4}" , ':' ,"Win"),
        std::format("State{:>17}{:>5}" , ':' ,"Lose"),
        std::format("State{:>17}{:>8}" , ':' ,"Restart"),
        std::format("State{:>17}{:>11}" ,':' ,"Waiting...")
    };
};

inline auto get_labels() -> const State_Label&
{
    static const auto labels = State_Label{};
    return labels;
}

struct Prompts
{
    std::array <std::string, 2> labels{
        "Are You\nSure?",
        "Log Win To\nDatabase?"
    };
};

inline auto get_prompts() -> const Prompts&
{
    static const auto messages = Prompts{};
    return messages;
}

#endif // STATE_HPP