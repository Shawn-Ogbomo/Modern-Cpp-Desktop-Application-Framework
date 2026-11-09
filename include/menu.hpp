#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <format>
#include <ranges>
#include <string>
#include <vector>

#include"../include/board.hpp"
#include "../include/button.hpp"
#include "../include/directory_manager.hpp"
#include "../include/random_number_gen.hpp"
#include "../include/refs.hpp"
#include "../include/sqlite3.h"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

struct Menu : public sf::Drawable
{
    static constexpr auto limit = 2;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual operator bool() const = 0;
    virtual ~Menu() = default;
};

template<typename T>
concept Is_Valid_Menu = std::derived_from<T, Menu>;

struct Game_State_Button : public Button
{
    Game_State_Button() = default;

    Game_State_Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) : forms{ txtrs }
    {
        configure_button(*this, val, target_label, pos);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;
    sf::Text label{ Util::load_font() };
    Properties<Button_Names::Game_State> contents;
};

struct Game_State_Menu : public Menu
{
    struct Lose_Condition
    {
        auto operator()(const Card& card)const ->bool;
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

    auto get_labels() & -> const State_Label&
    {
        static const auto labels = State_Label{};
        return labels;
    }

    explicit  Game_State_Menu(const General_Buttons& gb);

    auto operator()(const std::ranges::ref_view<std::deque<Card>> p, Refs_Components& r_c) -> void;
    auto operator++() & -> const Game_State_Menu&;

    operator bool() const override { return static_cast<bool>(mode); }

    auto update_game_state(auto g_state, Refs_Components& r_c) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Text move{ Util::load_font() };
    sf::Text game_id_t{ Util::load_font() };
    sf::Text game_state{ Util::load_font() };

    std::size_t game_id{};
    std::size_t move_count{};

    Button_Names::Game_State state{};
    Button_Names::Game_State state_prev{};

    std::span<Game_State_Button> gsbs{};
    std::array<Game_State_Button,Menu::limit> state_buttons;

    ButtonMode mode{ ButtonMode::on };
};

struct Exit_Button : public Button
{
    Exit_Button() = default;

    Exit_Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) : forms{ txtrs }
    {
        configure_button(*this, val, target_label, pos);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;
    sf::Text label{ Util::load_font() };
    Properties<Button_Names::Game_State> contents;
};

struct Exit_Menu : public Menu
{
    explicit  Exit_Menu(const General_Buttons& gb);
    operator bool() const override { return static_cast<bool>(mode); }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::span<Exit_Button> embs;
    std::array<Exit_Button,Menu::limit> buttons;

    ButtonMode mode{ ButtonMode::on };
};

struct Confirmation_Button : public Button
{
    Confirmation_Button() = default;
    
    Confirmation_Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) : forms{ txtrs }
    {
        configure_button(*this, val, target_label, pos);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;
    sf::Text label{ Util::load_font() };
    Properties<Button_Names::General> contents;
};

struct Confirmation_Menu : public Menu
{
    struct Prompts
    {
        std::array <std::string, 2> labels{
            "Are You\nSure?",
            "Log Win To\nDatabase?"
        };
    };

    auto get_prompts() & -> const Prompts&
    {
        static const auto messages = Prompts{};
        return messages;
    }

    explicit Confirmation_Menu(const General_Buttons& gb, const Text_Boxes& tb
        , std::span<const sf::RenderWindow>rws);

    operator bool() const override { return static_cast<bool>(mode); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    auto state_manager(Refs_Components& r_c) & ->void;

    std::span<Confirmation_Button> cbs;
    std::array<Confirmation_Button,Menu::limit> buttons{};

    sf::Text prompt{ Util::load_font() };
    sf::Sprite text_box{ default_texture() };

    ButtonMode mode{ ButtonMode::off };
};

struct Record
{
    //game id
    //game state
    
    // elapsed time
    //date -- includes local time 
};

struct Database_Button : public Button
{
    Database_Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) : forms{ txtrs }
    {
        configure_button(*this, val, target_label, pos);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;
    sf::Text label{ Util::load_font() };
    Properties<Button_Names::General> contents;
};

struct Database_Manager : public Menu
{
    Database_Manager();  ///create the table here.. evaluate it against exists table sqlite command 
    operator bool() const override{ return static_cast<bool>(mode); };
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite text_box{default_texture()};
    sf::Text indicator{Util::load_font()};  ///perhaps make this its own type with state and draw

    sf::RectangleShape text_field;

    std::unique_ptr<sqlite3*> conn;
    std::span<Database_Button> dbbs{};
    
    std::vector<Database_Button> buttons;
    std::vector<Record> recs;
    ButtonMode mode{};
};

auto read(Database_Manager&dmb);
auto write(Database_Manager& dbm);

#endif //MENU_HPP