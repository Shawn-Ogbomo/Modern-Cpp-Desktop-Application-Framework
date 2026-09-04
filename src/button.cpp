#include "../include/button.hpp"

namespace B_I = Button_Interface;
using B_I_N_M = Button_Interface::Button_Names::Media;

auto update_button(B_I_N_M& internal_name, std::tuple<sf::Sprite,sf::Sprite,sf::Sprite>& forms, int val, sf::Vector2f pos) ->void
{
    internal_name = static_cast<B_I_N_M>(val);            

    auto& [form_1, form_2, form_3] = forms;

    form_1.setPosition(pos);
    form_2.setPosition(pos);
    form_3.setPosition(pos);
}

Media_Button::Media_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, int val, sf::Vector2f pos)
    :forms{txtrs}
{
    update_button(name, forms, val, pos);
}

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

//Game_State_Button::Game_State_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, int val, sf::Vector2f pos)
//    :forms{ txtrs }
//{
//    update_button(name, forms, val, pos);
//}