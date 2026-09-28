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
        ///TODO: Disable the board here
        Button_Interface<Media_Button>::operator()(*this);
        gsm.operator()(Game_State::paused);
    }

    else if (name == B_N::Status::resume)
    {
        ///TODO: Enable the board here.
        Button_Interface<Media_Button>::operator()(*this);
        gsm.operator()(Game_State::playing);
    }
}