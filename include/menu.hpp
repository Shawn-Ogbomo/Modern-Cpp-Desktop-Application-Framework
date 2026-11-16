#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <format>
#include <ranges>
#include <string>
#include <vector>

#include "../include/button.hpp"
#include "../include/directory_manager.hpp"
#include "../include/random_number_gen.hpp"
#include "../include/component_manager.hpp"
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

//template <typename T>
//struct Buttons : Button
//{
//    Buttons() = default;
//
//    Buttons(const Texture_Forms& txtrs
//        , Button_Names::Game_State val, sf::Vector2f pos
//        , std::string_view target_label) : forms{ txtrs }
//    {
//        configure_button(*this, val, target_label, pos);
//    }
//
//    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
//    {
//        display_manager(*this, target);
//        target.draw(label);
//    }
//
//    Forms forms;
//    sf::Text label{ Util::load_font() };
//    Properties<T> contents;
//};

//struct Game_State_Button : public Button
//{
//    Game_State_Button() = default;
//
//    Game_State_Button(const Texture_Forms& txtrs
//        , Button_Names::Game_State val, sf::Vector2f pos
//        , std::string_view target_label) : forms{ txtrs }
//    {
//        configure_button(*this, val, target_label, pos);
//    }
//
//    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
//    {
//        display_manager(*this, target);
//        target.draw(label);
//    }
//
//    Forms forms;
//    sf::Text label{ Util::load_font() };
//    Properties<Button_Names::Game_State> contents;
//};

using CMB = Buttons <Button_Names::Confirm>;
using GSB = Buttons<Button_Names::Game_State>;
using EMB = Buttons < Button_Names::Exit>;
using DBB = Buttons<Button_Names::General>;

class Game_State_Menu : public Menu
{
    using Game_State_Buttons = std::array<GSB, Menu::limit>;
    using M_P = Menu_Properties<Game_State_Buttons, GSB>;
public:
    explicit  Game_State_Menu(const General_Buttons& gb);

    auto operator = (Game_State_Menu&&)
        -> Game_State_Menu & = delete;

    auto operator()(const std::ranges::ref_view<std::deque<Card>> p
        , Component_Manager& cm) -> void;

    auto operator++() & -> const Game_State_Menu&;
    operator bool() const override { return static_cast<bool>(menu_properties.mode); }

    auto clicked_button() & -> std::span<GSB>& { return menu_properties.spn; }

    auto update_game_state(Button_Names::Game_State g_state
        , Component_Manager& cm) & ->void;

    auto state() & -> ButtonMode& { return menu_properties.mode; };
    auto status() const& -> const Button_Names::Game_State& { return internal_state; }
    auto previous_status() const& -> const Button_Names::Game_State& { return state_prev; }
    auto buttons() & -> Game_State_Buttons& { return menu_properties.state_buttons; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    struct Lose_Condition
    {
        auto operator()(const Card& card)const ->bool;
    };

    sf::Text move{ Util::load_font() };
    sf::Text game_id_t{ Util::load_font() };
    sf::Text game_state{ Util::load_font() };

    std::size_t game_id{};
    std::size_t move_count{};

    Button_Names::Game_State internal_state{};
    Button_Names::Game_State state_prev{};

    M_P menu_properties{ ButtonMode::on };
};

//struct Exit_Button : public Button
//{
//    Exit_Button() = default;
//
//    Exit_Button(const Texture_Forms& txtrs
//        , Button_Names::Game_State val, sf::Vector2f pos
//        , std::string_view target_label) : forms{ txtrs }
//    {
//        configure_button(*this, val, target_label, pos);
//    }
//
//    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
//    {
//        display_manager(*this, target);
//        target.draw(label);
//    }
//    Forms forms;
//    sf::Text label{ Util::load_font() };
//    Properties<Button_Names::Game_State> contents;
//};

class Exit_Menu : public Menu
{
    using Exit_Buttons = std::array<EMB, Menu::limit>;
    using M_P = Menu_Properties<Exit_Buttons, EMB>;
public:
    explicit  Exit_Menu(const General_Buttons& gb);

    auto operator = (Exit_Menu&&)
        -> Exit_Menu & = delete;

    operator bool() const override { return static_cast<bool>(menu_properties.mode); }

    auto clicked_button() & -> std::span<EMB>& { return menu_properties.spn; }
    auto buttons() & -> Exit_Buttons& { return menu_properties.state_buttons; }
    auto state() & -> ButtonMode& { return menu_properties.mode; }
    auto restart() const& ->  bool { return internal_status; }
    [[nodiscard]] auto restart() & -> bool& { return internal_status; }
    auto state_manager(Component_Manager& c_m) & ->void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    bool internal_status{};
    M_P menu_properties{ ButtonMode::on };
};

//struct Confirmation_Button : public Button
//{
//    Confirmation_Button() = default;
//
//    Confirmation_Button(const Texture_Forms& txtrs
//        , Button_Names::General val, sf::Vector2f pos
//        , std::string_view target_label) : forms{ txtrs }
//    {
//        configure_button(*this, val, target_label, pos);
//    }
//
//    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
//    {
//        display_manager(*this, target);
//        target.draw(label);
//    }
//
//    Forms forms;
//    sf::Text label{ Util::load_font() };
//    Properties<Button_Names::General> contents;
//};

class Confirmation_Menu : public Menu
{
    using Confirmation_Buttons = std::array<CMB, Menu::limit>;
    using M_P = Menu_Properties<Confirmation_Buttons, CMB>;
public:
    explicit Confirmation_Menu(const General_Buttons& gb, const Text_Boxes& tb
        , std::span<const sf::RenderWindow>rws);

    auto operator = (Confirmation_Menu&&)
        -> Confirmation_Menu & = delete;

    operator bool() const override { return static_cast<bool>(menu_properties.mode); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    auto clicked_button() & -> std::span<CMB>& { return menu_properties.spn; }
    auto buttons() & -> Confirmation_Buttons& { return menu_properties.state_buttons; }
    auto state() & -> ButtonMode& { return menu_properties.mode; };
    auto state_manager(Component_Manager& c_m) & ->void;
private:
    sf::Text prompt{ Util::load_font() };
    sf::Sprite text_box{ default_texture() };
    M_P menu_properties;
};

struct Record
{
    int id{};
    int moves{};
    std::string alias;
    std::string elapsed_time;
    Button_Names::Game_State state{};
};

//struct Database_Button : public Button
//{
//    Database_Button() = default;
//
//    Database_Button(const Texture_Forms& txtrs
//        , Button_Names::General val, sf::Vector2f pos
//        , std::string_view target_label) : forms{ txtrs }
//    {
//        configure_button(*this, val, target_label, pos);
//    }
//
//    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
//    {
//        display_manager(*this, target);
//        target.draw(label);
//    }
//
//    Forms forms;
//    sf::Text label{ Util::load_font() };
//    Properties<Button_Names::General> contents;
//};

class Database_Manager : public Menu
{
    using Database_Buttons = std::array<DBB, limit + 1>;
    using M_P = Menu_Properties<Database_Buttons, DBB>;
public:
    Database_Manager();  ///Create the table here.. evaluate it against exists table SQLlite command

    auto operator = (Database_Manager&&)
        -> Database_Manager & = delete;

    operator bool() const override { return static_cast<bool>(menu_properties.mode); };

    auto state() & -> ButtonMode& { return menu_properties.mode; };
    auto clicked_button() & -> std::span<DBB>& { return menu_properties.spn; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Sprite text_box{ default_texture() };
    sf::Text indicator{ Util::load_font() };  ///perhaps make this its own type with state and draw
    sf::RectangleShape text_field;

    M_P menu_properties;

    std::unique_ptr<sqlite3*> conn;
    std::vector<Record> recs;
};

auto read(Database_Manager& dmb);
auto write(Database_Manager& dbm);

#endif //MENU_HPP