#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "config.hpp"

class BackgroundImage final : public Util::GameObject
{
public:
    enum class Screen
    {
        START_MENU,
        STORE_MENU,
        GAME_MENU,
    };

    BackgroundImage() : GameObject(
        std::make_unique<Util::Image>(RESOURCE_DIR"/image/background.png"), -10)
    {
        m_Transform.translation = {0.0F, 0.0F};
        UpdateScreen();
    }

    void SetScreen(const Screen screen);

    void UpdateScreen();

    Screen GetCurrentScreen() const { return m_CurrentScreen; }

private:
    Screen m_CurrentScreen = Screen::START_MENU;
};


#endif //BACKGROUNDIMAGE_H
