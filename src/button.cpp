#include "../include/button.hpp"

namespace B_N = Button_Names;

auto Media_Button::operator()(Music_Player& mp)const& ->void
{
    switch (name)
    {
    case B_N::Media::prev:
        mp.stop();
        mp.prev();
        mp.play();
        break;
    case B_N::Media::pause:
        mp.pause();
        break;
    case B_N::Media::play:
        mp.play();
        break;
    case B_N::Media::next:
        mp.stop();
        mp.next();
        mp.play();
        break;
    case B_N::Media::stop:
        mp.stop();
        break;
    }
}

auto Game_State_Button::operator()(Game_State_Menu& gsm)const& ->void
{
    if (name == B_N::Status::pause)
    {
        gsm.operator()(Game_State::paused);
    }

    else if (name == B_N::Status::resume)
    {
        gsm.operator()(Game_State::playing);
    }
}

auto Exit_Menu_Button::operator()(Exit_Menu& em) const&->void
{
    if (name == B_N::General::quit)
    {
        ///confirmation screen 
        ///close the window
    }

    else if (name == B_N::General::restart)
    {
        ///confirmation screen 
        ///restart application
    }
}
