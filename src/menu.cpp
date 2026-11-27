#include <format>

#include "../include/menu.hpp"

namespace B_N = Button_Names;
namespace rng = std::ranges;

using namespace std::string_view_literals;

Game_State_Menu::Game_State_Menu(const General_Buttons& gb)
    : internal_state{ B_N::Game_State::playing }
{
    game_id = Random_Number_Gen{ 100'000,999'999 }.random_number();

    menu_properties.state_buttons.front()
        = { gb.textures(),B_N::Game_State::paused,{ 417,800 }, "Pause" };

    menu_properties.state_buttons.back()
        = { gb.textures(),B_N::Game_State::playing,{ 502,800 }, "Resume" };

    game_id_t.setCharacterSize(26);
    game_id_t.setPosition({ 0, 790 });
    game_id_t.setFillColor({ 236,203,180 });
    game_id_t.setString(std::format("Game Id{:>12}{:>7}", ':', game_id));

    move.setCharacterSize(26);

    move.setPosition({ 0, 842 });
    move.setFillColor({ 236,203,180 });
    move.setString(std::format("Move{:>16}{:>2}", ':', move_count));

    game_state.setCharacterSize(26);
    game_state.setPosition({ 0, 816 });
    game_state.setFillColor({ 236,203,180 });
    game_state.setString(*(get_labels().states.begin() + 1));
}

auto Game_State_Menu::operator()(const rng::ref_view<std::deque<Card>> p
    , Component_Manager& r_c) -> void
{
    if (move_count == cards_pile * total_piles) [[unlikely]]
    {
        update_game_state(B_N::Game_State::win, r_c);
        return;
    }

    if (const auto num_kings = rng::count_if(p, Lose_Condition()); num_kings
        == cards_pile)
    {
        update_game_state(B_N::Game_State::lose, r_c);
    }
}

auto Game_State_Menu::operator++() & -> const Game_State_Menu&
{
    ++move_count;

    move_count > 9
        ? move.setString(std::format("Move{:>16}{:>3}", ':', move_count))
        : move.setString(std::format("Move{:>16}{:>2}", ':', move_count));

    return *this;
}

void Game_State_Menu::draw(sf::RenderTarget& target
    , sf::RenderStates states) const
{
    target.draw(game_id_t);
    target.draw(move);
    target.draw(game_state);
    target.draw(menu_properties.state_buttons.front());
    target.draw(menu_properties.state_buttons.back());
}

auto Game_State_Menu::update_game_state(B_N::Game_State g_state
    , Component_Manager& cm) & -> void
{
    internal_state = g_state;

    game_state.setString(get_labels()
        .states[static_cast<int>(internal_state)]);

    switch (internal_state)
    {
    case B_N::Game_State::playing:
        enable_components(cm);
        break;
    case B_N::Game_State::paused:
        disable_components(cm);
        cm.enable_game_state_menu();
        cm.enable_exit_menu();
        break;
    case B_N::Game_State::win:
        disable_components(cm);
        cm.enable_confirmation_menu();
        break;
    case B_N::Game_State::lose:
        disable_components(cm);
        cm.enable_exit_menu();
        break;
    }
}

auto Game_State_Menu::Lose_Condition::operator()(const Card& card)const ->bool
{
    return card.rank() == Rank_Lib::Rank::king &&
        card.state() == Card_State::face_up;
}

Exit_Menu::Exit_Menu(const General_Buttons& gb)
{
    menu_properties.state_buttons.front()
        = { gb.textures(), B_N::Exit::restart,{ 5, 0 }, "Reset" };

    menu_properties.state_buttons.back()
        = { gb.textures(), B_N::Exit::quit,{ 5, 40 }, "Quit" };
}

auto Exit_Menu::state_manager(Component_Manager& cm) & ->void
{
    if (const auto& reset = menu_properties.state_buttons.front())
    {
        cm.restart_game();
    }

    else if (const auto& quit = menu_properties.state_buttons.back())
    {
        disable_components(cm);
        cm.enable_confirmation_menu();
    }
}

void Exit_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(menu_properties.state_buttons.front());
    target.draw(menu_properties.state_buttons.back());
}

Confirmation_Menu::Confirmation_Menu(const General_Buttons& gb, sf::Sprite& tb,
    const sf::RenderWindow& rws)
    : internal_text_box{ get_prompts().labels.front(),tb, rws }
{
    const auto dimensions_textbox = sf::Vector2f{ tb.getGlobalBounds().size };

    configure_buttons("No"sv, "Yes"sv, menu_properties.state_buttons
        , gb, internal_text_box, B_N::Confirm::no);
}

void Confirmation_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (menu_properties.mode == ButtonMode::on)
    {
        target.draw(internal_text_box);
        target.draw(menu_properties.state_buttons.front());
        target.draw(menu_properties.state_buttons.back());
    }
}

auto Confirmation_Menu::state_manager(Component_Manager& cm) & ->void
{
    disable_confirmation_menus(cm);

    const auto& clicked_button = [&, this](const auto& b) -> bool
        { return b; };

    auto found = rng::find_if(menu_properties.state_buttons
        , clicked_button);

    if (found != std::end(menu_properties.state_buttons))
    {
        if (found->contents.name == B_N::Confirm::no)
        {
            ///TODO: Go back to previous state
        }

        else if (found->contents.name == B_N::Confirm::yes)
        {
            ///TODO: check if quit is confirmation is enabled
            ///TODO: close application
            cm.enable_confirmation_menu();
        }
    }
}

Input_Menu::Input_Menu(const General_Buttons& gb, sf::Sprite& tb
    , const sf::RenderWindow& rws) : internal_text_box{ get_prompts().labels.back(),tb,
    rws, sf::RectangleShape{} }
{
    configure_buttons("Cancel"sv, "OK"sv, menu_properties.state_buttons
        , gb, internal_text_box, B_N::Confirm_Input::cancel);
}

auto Input_Menu::state_manager(Component_Manager& c_m) & ->void
{}

void Input_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (menu_properties.mode == ButtonMode::on)
    {
        target.draw(internal_text_box);
        target.draw(menu_properties.state_buttons.front());
        target.draw(menu_properties.state_buttons.back());
    }
}

Database_Manager::Database_Manager() :conn{ std::make_unique<sqlite3*>() }
{
    /// TODO: open a database connection
    /// Create a table, if it exists sqlite won't create it.
    /// Try implementing a user-defined delete to avoid calling close() on the database connection explicitly.

    ///TODO: Don't use a raw path for parameter 1.
    if (const auto fail = sqlite3_open("../../../../data/data.db", &(*conn)); fail)
    {
        /// TODO:Throw an exception...
        /// Provide a meaningful diagnostic. Use std::Path
        throw std::invalid_argument{ "Invalid File...\n" };
    }

    ///TODO: Prepare SQLite commands by converting them to byte code before use.
    const auto create_query = std::format(
        "CREATE TABLE IF NOT EXISTS LEADERBOARD("
        "alias TEXT NOT NULL,"
        "game_id INTEGER PRIMARY KEY UNIQUE,"
        "game_state TEXT NOT NULL,"
        "elapsed_time TEXT NOT NULL,"
        "local_time TEXT NOT NULL)");

    ///Construct a query to read, write, and sort by date -- order by.
    /// with write if the database is full -- 20 records, overwrite the oldest record
    /// create another query to sort the database by date.
    /// Date should be YY/MM/DD it will be easier to sort this way -- year num, month num 00 Jan is 1st since it is 01
    ///Dec is last since it is 12
    ///write your query to the database using your time status local time to help then parse it?

    ///When writing a record to database validate the alias against duplicates.

    ///Create a function to store all of your queries, compile, and execute them.

    ///Create query is compiled here.
    sqlite3_stmt* converted_create_query{};

    ///End of last query goes here,
    const char** nothing{};

    /// Returns 26. The if file is empty and not in SQLite format.
    /// Don't create the file yourself.

    sqlite3_prepare_v2(*conn, create_query.c_str(), -1, &converted_create_query, nothing);

    /// Executes query and advances the pointer.
    sqlite3_step(converted_create_query);
}

void Database_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (menu_properties.mode == ButtonMode::on)
    {
        target.draw(text_box);
        target.draw(text_field);
        target.draw(indicator);
        target.draw(menu_properties.state_buttons.front());
        target.draw(*(menu_properties.state_buttons.begin() + 1));
        target.draw(menu_properties.state_buttons.back());
    }
}