#include "Menus/StartMenu.h"
#include "App.hpp"
#include "UI/Picture.h"

void StartMenu::Open()
{
    m_MinerPicture = std::make_shared<UI::Picture>(RESOURCE_DIR"/Picture/gold-miner-text.png", 1);
    m_MinerPicture->SetPosition({0, 100});
    AddChild(m_MinerPicture);

    m_StartButton = std::make_shared<UI::Button>(RESOURCE_DIR"/Picture/start-1.png", 1);
    m_StartButton->SetPosition({0, -50});
    AddChild(m_StartButton);
}

void StartMenu::Update(App* app)
{
    if (m_StartButton->OnHover())
        m_StartButton->SetImage(RESOURCE_DIR"/Picture/start-2.png");
    else
        m_StartButton->SetImage(RESOURCE_DIR"/Picture/start-1.png");
    if (m_StartButton->IsClicked())
    {
        printf("[~] Click StartButton\n");
        app->ChangeMenu(Screen::GAME_MENU);
    }
}

void StartMenu::Close()
{
    printf("[~] Close StartMenu\n");
    auto children = GetChildren();
    for (const auto& child : children)
        RemoveChild(child);
}
