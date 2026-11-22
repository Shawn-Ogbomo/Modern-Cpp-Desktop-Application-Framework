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
        if (cm.front().buttons()[static_cast<int>(B_N::Confirm::yes)])
        {
            cm.front().text_boxes().back().state() = ButtonMode::on;

            cm.front().text_boxes().back().prompt()
                .setString((get_prompts().labels.back()));

            return;
        }

        cm.front().text_boxes().front().state() = ButtonMode::on;

        cm.front().text_boxes().front().prompt()
            .setString(get_prompts()
                .labels[static_cast<int>(MSG::log_database)]);
    }

    else if (em.front().buttons()[static_cast<int>(B_N::Exit::quit)])
    {
        cm.front().text_boxes().front().state() = ButtonMode::on;

        cm.front().text_boxes().front().prompt()
            .setString((get_prompts().labels.front()));
    }
}

auto::Component_Manager::enable_components()const& ->void
{
    cl.front().start();
    board.front().state() = ButtonMode::on;
    em.front().state() = ButtonMode::on;
    mp.front().state() = ButtonMode::on;
    gsm.front().state() = ButtonMode::on;
};

auto Component_Manager::restart_game() & ->void
{
    em.front().restart() = true;
}

auto::Component_Manager::disable_components()const& -> void
{
    cl.front().stop();
    board.front().state() = ButtonMode::off;
    em.front().state() = ButtonMode::off;
    mp.front().state() = ButtonMode::off;
    gsm.front().state() = ButtonMode::off;
    cm.front().state() = ButtonMode::off;
};

auto Component_Manager::disable_confirmation_menus()const& ->void
{
    cm.front().state() = ButtonMode::off;
    cm.front().text_boxes().front().state() = ButtonMode::off;
    cm.front().text_boxes().back().state() = ButtonMode::off;
}

auto Component_Manager::close_window() const& ->void
{
    app_state.front() = false;
    rw.front().close();
}