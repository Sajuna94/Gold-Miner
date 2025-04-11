#include "Menus/GameMenu.h"
#include "App.hpp"
#include "Util/Input.hpp"

void GameMenu::Stop()
{

}


void GameMenu::Open(Util::Renderer* m_Root)
{
    m_Miner = std::make_shared<Miner>();
    m_Root->AddChild(m_Miner);
}

void GameMenu::Update(App* app)
{
    // throw pickaxe
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB))
    {

    }
}

void GameMenu::Close(Util::Renderer* m_Root) const
{
    printf("[~] Close GameMenu\n");
}
