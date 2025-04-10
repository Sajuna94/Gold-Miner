#include "Menus/GameMenu.h"
#include "App.hpp"

void GameMenu::Open()
{
    m_Miner = std::make_shared<Miner>();
    m_Root.AddChild(m_Miner);
}

void GameMenu::Update(App* app)
{
}

void GameMenu::Close()
{
    printf("[~] Close GameMenu\n");
}
