#include "Menus/StartMenu.h"
#include "App.hpp"

void StartMenu::Open()
{
    m_StartButton = std::make_shared<UI::Button>(RESOURCE_DIR"/res/iphonehd/gold-miner-text.png");
    m_StartButton->SetPosition({0.5f, 0.5f});

    m_Root->AddChild(m_StartButton);
}

void StartMenu::Update(App* app)
{
    if (m_StartButton->IsClicked())
    {
        printf("[~] Click StartButton\n");
        app->ChangeMenu(Screen::GAME_MENU);
    }
}

void StartMenu::Close()
{
    printf("[~] Close StartMenu\n");
    m_Root->RemoveChild(m_StartButton);
}
