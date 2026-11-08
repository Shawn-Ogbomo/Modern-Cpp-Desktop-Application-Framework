#include <format>

#include "../include/menu.hpp"

namespace B_N = Button_Names;
namespace rng = std::ranges;

using namespace std::literals;

Game_State_Menu::Game_State_Menu(const General_Buttons& gb)
{
    Random_Number_Gen rng{ 100'000,999'999 };
    game_id = rng.dst(rng.g);

    state_buttons.reserve(Menu::limit);

    state_buttons.push_back({ gb.textures,B_N::Game_State::paused, {417,800}, "Pause" });
    state_buttons.push_back({ gb.textures,B_N::Game_State::playing, {502,800}, "Resume" });

    game_id_t.setCharacterSize(26);
    game_id_t.setPosition({ 0, 790 });
    game_id_t.setFillColor({ 236,203,180 });
    game_id_t.setString(std::format("Game Id{:>12}{:>7}" , ':' ,game_id));

    move.setCharacterSize(26);

    move.setPosition({ 0, 842 });
    move.setFillColor({ 236,203,180 });
    move.setString(std::format( "Move{:>16}{:>2}",':' , move_count));

    state = B_N::Game_State::playing;

    game_state.setCharacterSize(26);
    game_state.setPosition({ 0, 816 });
    game_state.setFillColor({ 236,203,180 });
    game_state.setString(get_labels().states[static_cast<int>(state)]);
}

auto Game_State_Menu::operator()(const rng::ref_view<std::deque<Card>> p, Refs_Components& r_c) -> void
{
    if (move_count == Board::cards_pile * Board::total_piles) [[unlikely]]
    {
        update_game_state(B_N::Game_State::win, r_c);
        return;
    }

    if (const auto num_kings = rng::count_if(p, Lose_Condition()); num_kings == Board::cards_pile)
    {
        update_game_state(B_N::Game_State::lose, r_c);
    }
}

auto Game_State_Menu::operator++() & -> const Game_State_Menu&
{
    ++move_count;
    move_count > 9 ? move.setString(std::format("Move{:>16}{:>3}", ':', move_count)) 
        : move.setString(std::format("Move{:>16}{:>2}", ':', move_count));
    return *this;
}

void Game_State_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(game_id_t);
    target.draw(move);
    target.draw(game_state);
    target.draw(state_buttons.front());
    target.draw(state_buttons.back());
}

auto Game_State_Menu::update_game_state(auto g_state, Refs_Components& r_c) & -> void
{
    const auto& disable_piles = [&, this]
        {
            r_c.sp2_b.front().piles[static_cast<int>(r_c.sp2_b.front().pos_prev)].active = false;
        };

    const auto& enable_piles = [&, this]
        {
            r_c.sp2_b.front().piles[static_cast<int>(r_c.sp2_b.front().pos_prev)].active = true;
        };

    const auto& enable_components = [&, this]
        {
            enable_piles();
            r_c.sp3_c.front().start();
            r_c.sp4_em.front().mode = ButtonMode::on;
            r_c.sp7_gsm.front().mode = ButtonMode::on;
            r_c.sp5_mp.front().mode = ButtonMode::on;
        };

    const auto& disable_components = [&, this]
        {
            disable_piles();
            r_c.sp3_c.front().stop();
            r_c.sp5_mp.front().mode = ButtonMode::off;
        };

    state_prev = state;
    state = g_state;

    game_state.setString(get_labels()
        .states[static_cast<int>(state)]);

    switch (state)
    {
    case B_N::Game_State::playing:
    case B_N::Game_State::restart:
        enable_components();
        break;
    case B_N::Game_State::paused:
        disable_components();
        r_c.sp7_gsm.front().mode = ButtonMode::on;
        r_c.sp4_em.front().mode = ButtonMode::on;
        break;
    case B_N::Game_State::win:
        disable_components();
        r_c.sp8_cm.front().prompt.setString(r_c.sp8_cm.front()
            .get_prompts().labels.back());

        r_c.sp7_gsm.front().mode = ButtonMode::off;
        r_c.sp4_em.front().mode = ButtonMode::on;
        r_c.sp8_cm.front().mode = ButtonMode::on;
        break;
    case B_N::Game_State::lose:
        disable_components();
        r_c.sp7_gsm.front().mode = ButtonMode::off;
        r_c.sp4_em.front().mode = ButtonMode::on;
        break;
    case B_N::Game_State::quit:
        disable_components();
        r_c.sp8_cm.front().prompt.setString(r_c.sp8_cm.front()
            .get_prompts().labels.front());
        r_c.sp4_em.front().mode = ButtonMode::off;
        r_c.sp7_gsm.front().mode = ButtonMode::off;
        r_c.sp8_cm.front().mode = ButtonMode::on;
        break;
    }
}

auto Game_State_Menu::Lose_Condition::operator()(const Card& card)const ->bool
{
    return card.rank== Rank_Lib::Rank::king &&
        card.state == Card_State::face_up;
}

Exit_Menu::Exit_Menu(const General_Buttons& gb)
{
    buttons.reserve(Menu::limit);

    buttons.push_back({ gb.textures, B_N::Game_State::restart, {5, 0}, "Reset" });
    buttons.push_back({ gb.textures, B_N::Game_State::quit, {5, 40}, "Quit" });
}

void Exit_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(buttons.front());
    target.draw(buttons.back());
}

Confirmation_Menu::Confirmation_Menu(const General_Buttons& gb, const Text_Boxes& tb,
    std::span<const sf::RenderWindow>rws) : text_box{ tb.t }
{
    prompt.setString(get_prompts().labels.front());

    buttons.reserve(Menu::limit);

    prompt.setFillColor({ 236,203,180 });
    prompt.setCharacterSize(26);

    const auto dimensions_window = static_cast<sf::Vector2f>(rws.front().getSize());
    const auto dimensions_textbox = sf::Vector2f{ text_box.getGlobalBounds().size };
    const auto dimensions_prompt = prompt.getGlobalBounds().size;

    prompt.setPosition({ ((dimensions_window.x - dimensions_textbox.x) / 2) + (dimensions_textbox.x / 2)
        - (dimensions_prompt.x / 2) , ((dimensions_window.y - dimensions_textbox.y) / 2)
        + (dimensions_textbox.y / 2) - dimensions_prompt.y });

    text_box.setPosition({ (dimensions_window.x - dimensions_textbox.x) / 2
        , (dimensions_window.y - dimensions_textbox.y) / 2 });

    buttons.push_back({ gb.textures, B_N::General::yes, {417, text_box.getGlobalBounds().position.y
        + dimensions_textbox.y - 50}, "Yes" });

    buttons.push_back({ gb.textures, B_N::General::no, {502,  text_box.getGlobalBounds().position.y
        + dimensions_textbox.y - 50}, "No" });
}

void Confirmation_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mode == ButtonMode::on)
    {
        target.draw(text_box);
        target.draw(prompt);
        target.draw(buttons.front());
        target.draw(buttons.back());
    }
}

auto Confirmation_Menu::state_manager(Refs_Components& r_c) & ->void
{
    if (buttons.front().contents.setting == ButtonMode::on) 
    {
        r_c.sp1_b.front() = false;
        r_c.sp6_rw.front().close();
        return;
    }

    r_c.sp7_gsm.front().update_game_state(r_c.sp7_gsm.front().state_prev, r_c);
    r_c.sp8_cm.front().mode = ButtonMode::off;
}

Database_Manager::Database_Manager() :conn{ std::make_unique<sqlite3*>() }
{
    /// TODO: open a database connection
    /// Create a table, if it exists sqlite won't create it. 
    /// Try implementing a user-defined delete to avoid calling close() on the database connection explicitly. 

    ///TODO: Don't use a raw path for parameter 1. 
    if (const auto fail= sqlite3_open("../../../../data/data.db", &(*conn)); fail)
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
    if (mode == ButtonMode::on)
    {
        target.draw(text_box);
        target.draw(text_field);
        target.draw(indicator);
        target.draw(buttons.front());
        target.draw(*(buttons.begin() +1));
        target.draw(buttons.back());
    }
 }