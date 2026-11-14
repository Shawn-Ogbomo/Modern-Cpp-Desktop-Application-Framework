#include "../include/component_manager.hpp"
#include "../include/menu.hpp"

auto::Component_Manager::enable_exit_menu()const& ->void
{
    sp4_em.front().state() = ButtonMode::on;
}

auto::Component_Manager::enable_game_state_menu()const& ->void
{
    sp7_gsm.front().state() = ButtonMode::on;
}

auto::Component_Manager::enable_confirmation_menu()const& ->void
{
    sp8_cm.front().state() = ButtonMode::on;
}

auto::Component_Manager::enable_components()const& ->void
{
    sp3_c.front().start();
    sp2_b.front().state() = ButtonMode::on;
    sp4_em.front().state() = ButtonMode::on;
    sp5_mp.front().state() = ButtonMode::on;
    sp7_gsm.front().state() = ButtonMode::on;
};

auto::Component_Manager::disable_components()const& -> void
{
    sp3_c.front().stop();
    sp2_b.front().state() = ButtonMode::off;
    sp4_em.front().state() = ButtonMode::off;
    sp5_mp.front().state() = ButtonMode::off;
    sp7_gsm.front().state() = ButtonMode::off;
    sp8_cm.front().state() = ButtonMode::off;
};

auto Component_Manager::disable_confirmation_menu()const& ->void
{
    sp8_cm.front().state() = ButtonMode::off;
}

auto Component_Manager::close_window() const& ->void
{
    sp6_rw.front().close();
}

auto Component_Manager::disable_automatic_restart() const& -> void
{
    sp1_b.front() = false;
}

auto Component_Manager::previous_game_state() & -> void
{
    sp7_gsm.front().update_game_state(sp7_gsm.front().previous_status(), *this);
}