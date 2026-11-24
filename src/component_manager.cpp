#include "../include/component_manager.hpp"
#include "../include/menu.hpp"

namespace B_N = Button_Names;

auto::Component_Manager::enable_exit_menu()const& ->void
{
    em.front().state() = ButtonMode::on;
}

auto::Component_Manager::enable_game_state_menu()const& ->void
{
    gsm.front().state() = ButtonMode::on;
}

auto::Component_Manager::enable_confirmation_menu()const& ->void
{
    cm.front().state() = ButtonMode::on;

    if (gsm.front().status() == B_N::Game_State::win)
    {
        if (const auto& yes = (*(cm.front().buttons().begin()+1)))
        {
            cm.front().text_boxes().back().state() = ButtonMode::on;

            cm.front().text_boxes().back().prompt()
                .setString((get_prompts().labels.back()));

            return;
        }

        cm.front().text_boxes().front().state() = ButtonMode::on;

        cm.front().text_boxes().front().prompt()
            .setString(*(get_prompts()
                .labels.begin()+1));
    }

    else if (const auto& quit = em.front().buttons().back())
    {
        cm.front().text_boxes().front().state() = ButtonMode::on;

        cm.front().text_boxes().front().prompt()
            .setString((get_prompts().labels.front()));
    }
}

auto Component_Manager::disable_exit_menu() const& -> void
{
    em.front().state() = ButtonMode::off;

}
auto Component_Manager::disable_game_state_menu() const& -> void
{
    gsm.front().state() = ButtonMode::off;
}

auto Component_Manager::disable_confirmation_menu() const& -> void
{
    cm.front().state() = ButtonMode::off;
}

auto disable_confirmation_menus(Component_Manager& cm) -> void
{
    cm.disable_confirmation_menu();
    cm.disable_text_box();
    cm.disable_text_box_input();
}

auto Component_Manager::enable_clock() const& ->void
{
    cl.front().start();
}

auto Component_Manager::enable_music_player() const& ->void
{
    mp.front().state() = ButtonMode::on;
}

auto Component_Manager::enable_board() const& ->void
{
    board.front().state() = ButtonMode::on;
}

auto enable_components(Component_Manager& cm) -> void
{
    cm.enable_clock();
    cm.enable_board();
    cm.enable_music_player();
    cm.enable_exit_menu();
    cm.enable_game_state_menu();
}

auto Component_Manager::disable_text_box() const& ->void
{
    cm.front().text_boxes().front().state() = ButtonMode::off;
}

auto Component_Manager::disable_text_box_input() const& ->void
{
    cm.front().text_boxes().back().state() = ButtonMode::off;
}

auto Component_Manager::restart_game() & ->void
{
    em.front().restart() = true;
}

auto Component_Manager::close_window() const& ->void
{
    app_state.front() = false;
    rw.front().close();
}

auto Component_Manager::disable_clock() const& -> void
{
    cl.front().stop();
}

auto Component_Manager::disable_board() const& -> void
{
    board.front().state() = ButtonMode::off;
}

auto Component_Manager::disable_music_player() const& -> void
{
    mp.front().state() = ButtonMode::off;
}

auto disable_components(Component_Manager& cm) -> void
{
    cm.disable_clock();
    cm.disable_board();
    cm.disable_music_player();
    cm.disable_exit_menu();
    cm.disable_game_state_menu();
    cm.disable_confirmation_menu();
}
