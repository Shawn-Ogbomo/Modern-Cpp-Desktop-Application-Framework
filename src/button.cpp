#include "../include/button.hpp"

namespace B_I = Button_Interface;

auto Media_Button::operator()(Music_Player& mp)const & -> void
{
    switch (name)
    {
    case B_I::Button_Names::Media::prev:
        mp.stop();
        mp.prev();
        mp.play();
        break;
    case B_I::Button_Names::Media::pause:
        mp.pause();
        break;
    case B_I::Button_Names::Media::play:
        mp.play();
        break;
    case B_I::Button_Names::Media::next:
        mp.stop();
        mp.next();
        mp.play();
        break;
    case B_I::Button_Names::Media::stop:
        mp.stop();
        break;
    }
}