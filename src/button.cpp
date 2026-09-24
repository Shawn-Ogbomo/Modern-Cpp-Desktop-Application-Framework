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
       
    }

    if (name == B_N::Status::resume)
    {

    }
}