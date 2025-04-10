#include "BackgroundImage.h"

void BackgroundImage::SetScreen(const Screen screen)
{
    m_CurrentScreen = screen;
    UpdateScreen();
}

void BackgroundImage::UpdateScreen()
{
    auto const temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);

    switch (m_CurrentScreen)
    {
    case Screen::START_MENU:
        temp->SetImage(RESOURCE_DIR"/image/background.png");
        break;
    case Screen::GAME_MENU:
        temp->SetImage(RESOURCE_DIR"/image/background.bmp");
        break;
    case Screen::STORE_MENU:
        temp->SetImage(RESOURCE_DIR"/res/iphonehd/shop-background.jpg");
        break;
    default:
        printf("[!] wrong screen enum\n");
    }

    glm::vec2 const size = temp->GetSize();
    m_Transform.scale = {WINDOW_WIDTH / size.x, WINDOW_HEIGHT / size.y};
}
