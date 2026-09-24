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
       ///TODO: change the game state to paused 
       /// If the game state is playing 
        /// save the active pile 
        /// set it to inactive, now no cards can move while the game is paused
        /// disable all media buttons, but allow the music to play if it was playing before the pause. 
        /// remove the pause button and draw the resume button in the same place as the pause button
    }

    if (name == B_N::Status::resume)
    {
        ///TODO: Do the inverse of pause 
        /// If game state is paused
        /// set the active pile to the one that was saved 
        /// enable all media buttons 
        /// remove the resume button and draw the paused button in the same place
    }
}