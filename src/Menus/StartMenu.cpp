#include "Menus/StartMenu.h"
#include "App.hpp"
#include "UI/Picture.h"

void StartMenu::Open()
{
    m_MinerPicture = std::make_shared<UI::Picture>(RESOURCE_DIR"/Picture/gold-miner-text.png");
    m_MinerPicture->SetPosition({0, 100});
    m_Root->AddChild(m_MinerPicture);

    m_StartButton = std::make_shared<UI::Button>(RESOURCE_DIR"/Button/start-1.png");
    m_StartButton->SetPosition({0, -50});
    m_Root->AddChild(m_StartButton);
}

void StartMenu::Update(App* app)
{
    if (m_StartButton->OnHover())
        m_StartButton->SetImage(RESOURCE_DIR"/Button/start-2.png");
    else
        m_StartButton->SetImage(RESOURCE_DIR"/Button/start-1.png");
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
    m_Root->RemoveChild(m_MinerPicture);
}
