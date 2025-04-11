#include "Menus/GameMenu.h"
#include "App.hpp"
#include "UI/Text.h"
#include "Util/Input.hpp"
#include <iostream>
void GameMenu::Open()
{
    m_Miner = std::make_shared<Miner>();
    m_Root->AddChild(m_Miner);

    m_Pickaxe = std::make_shared<Pickaxe>();
    m_Root->AddChild(m_Pickaxe);

    m_OreList.push_back(std::make_shared<Diamond>());
    for (auto& ore : m_OreList)
        m_Root->AddChild(ore);

    m_TimerText = std::make_shared<UI::Text>("TIME", 20);
    m_TimerText->SetPosition({WINDOW_WIDTH / 2.0 - m_TimerText->GetScaledSize().x, WINDOW_HEIGHT / 2 - 20});
    m_Root->AddChild(m_TimerText);

    printf("WINDOW_SIZE: %d, %d", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameMenu::Update(App* app)
{
    m_Pickaxe->Update();
    m_TimerText->SetText(std::to_string(Util::Time::GetDeltaTimeMs()));

    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB))
    {
        m_Pickaxe->Throw();
    }
}

void GameMenu::Close()
{
    for (auto& ore : m_OreList)
    {
        m_Root->RemoveChild(ore);
    }

    printf("[~] Close GameMenu\n");
}
