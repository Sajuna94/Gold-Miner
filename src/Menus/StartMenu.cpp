#include "Menus/StartMenu.h"
#include "App.hpp"

void StartMenu::Open()
{
    m_StartButton = std::make_shared<Button>(RESOURCE_DIR"/res/iphonehd/gold-miner-text.png");
    m_StartButton->SetPosition({0.5f, 0.5f});

    m_Root.AddChild(m_StartButton);
}

void StartMenu::Update(App* app)
{
    if (m_StartButton->CheckClick())
    {
        printf("[~] Click StartButton\n");

        // update game background
        app->GetBackgroundImage()->SetScreen(BackgroundImage::Screen::GAME_MENU);
        // close start menu
        Close();
        // open game menu
        app->GetGameMenu()->Open();
    }
}

void StartMenu::Close()
{
    printf("[~] Close StartMenu\n");
    m_Root.RemoveChild(m_StartButton);
}
