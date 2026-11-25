#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <format>
#include <ranges>
#include <string>
#include <vector>

#include "../include/button.hpp"
#include "../include/component_manager.hpp"
#include "../include/directory_manager.hpp"
#include "../include/random_number_gen.hpp"
#include "../include/sqlite3.h"
#include "../include/state.hpp"
#include "../include/text_box.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

namespace
{
    constexpr auto limit = 2;
    constexpr auto text_box_limit = 3;
    using CMB = Button <Button_Names::Confirm>;
    using IMB = Button <Button_Names::Confirm_Input>;
    using GSB = Button <Button_Names::Game_State>;
    using EMB = Button < Button_Names::Exit>;
    using DBB = Button <Button_Names::General>;
};

class Game_State_Menu : public sf::Drawable
{
    using Game_State_Buttons = std::array<GSB, limit>;
    using M_P = Menu_Properties<Game_State_Buttons, GSB>;
public:
    explicit  Game_State_Menu(const General_Buttons& gb);

    auto operator = (Game_State_Menu&&)
        -> Game_State_Menu & = delete;

    auto operator()(const std::ranges::ref_view<std::deque<Card>> p
        , Component_Manager& cm) -> void;

    auto operator++() & -> const Game_State_Menu&;
    operator bool() const { return static_cast<bool>(menu_properties.mode); }

    auto clicked_button() & -> std::span<GSB>& { return menu_properties.spn; }

    auto update_game_state(Button_Names::Game_State g_state
        , Component_Manager& cm) & ->void;

    auto state() & -> ButtonMode& { return menu_properties.mode; };
    auto status() const& -> const Button_Names::Game_State& { return internal_state; }
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
    M_P menu_properties{ ButtonMode::on };
};

class Exit_Menu : public sf::Drawable
{
    using Exit_Buttons = std::array<EMB, limit>;
    using M_P = Menu_Properties<Exit_Buttons, EMB>;
public:
    explicit  Exit_Menu(const General_Buttons& gb);

    auto operator = (Exit_Menu&&)
        -> Exit_Menu & = delete;

    operator bool() const { return static_cast<bool>(menu_properties.mode); }

    auto clicked_button() & -> std::span<EMB>& { return menu_properties.spn; }
    auto buttons() & -> Exit_Buttons& { return menu_properties.state_buttons; }
    auto state() & -> ButtonMode& { return menu_properties.mode; }
    auto restart() const& ->  bool { return internal_status; }
    auto restart() & -> bool& { return internal_status; }
    auto state_manager(Component_Manager& c_m) & ->void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    bool internal_status{};
    M_P menu_properties{ ButtonMode::on };
};

class Confirmation_Menu : public sf::Drawable
{
    using Confirmation_Buttons = std::array<CMB, limit>;
    using M_P = Menu_Properties<Confirmation_Buttons, CMB>;
public:
    explicit Confirmation_Menu(const General_Buttons& gb, sf::Sprite& tb
        , const sf::RenderWindow& rws);

    auto operator = (Confirmation_Menu&&)
        -> Confirmation_Menu & = delete;

    operator bool() const { return static_cast<bool>(menu_properties.mode); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    auto clicked_button() & -> std::span<CMB>& { return menu_properties.spn; }
    auto buttons() & -> Confirmation_Buttons& { return menu_properties.state_buttons; }
    auto state() & -> ButtonMode& { return menu_properties.mode; };
    auto state_manager(Component_Manager& c_m) & ->void;
    auto text_box() & -> Text_Box& { return internal_text_box; }
private:
    Text_Box internal_text_box;
    M_P menu_properties;
};

class Input_Menu : public sf::Drawable
{
    using Input_Buttons = std::array<IMB, limit>;
    using M_P = Menu_Properties<Input_Buttons, IMB>;
public:
    explicit Input_Menu(const General_Buttons& gb, sf::Sprite& tb
        , const sf::RenderWindow& rw);

    auto operator = (Input_Menu&&)
        -> Input_Menu & = delete;

    operator bool() const { return static_cast<bool>(menu_properties.mode); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    auto clicked_button() & -> std::span<IMB>& { return menu_properties.spn; }
    auto buttons() & -> Input_Buttons& { return menu_properties.state_buttons; }
    auto state() & -> ButtonMode& { return menu_properties.mode; };
    auto state_manager(Component_Manager& c_m) & ->void;
    auto text_box() & -> Input_Box& { return internal_text_box; }
private:
    Input_Box internal_text_box;
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

class Database_Manager : public sf::Drawable
{
    using Database_Buttons = std::array<DBB, limit + 1>;
    using M_P = Menu_Properties<Database_Buttons, DBB>;
public:
    Database_Manager();  ///Create the table here.. evaluate it against exists table SQLlite command

    auto operator = (Database_Manager&&)
        -> Database_Manager & = delete;

    operator bool() const { return static_cast<bool>(menu_properties.mode); };

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