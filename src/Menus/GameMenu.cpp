#include "Menus/GameMenu.h"
#include "App.hpp"

void GameMenu::Open() {
    m_Miner = std::make_shared<Miner>();
    m_Root->AddChild(m_Miner);

    m_OreList.push_back(std::make_shared<Diamond>());

    for (auto &ore: m_OreList) {
        m_Root->AddChild(ore);
    }
}

void GameMenu::Update(App *app) {
}

void GameMenu::Close() {
    for (auto &ore: m_OreList) {
        m_Root->RemoveChild(ore);
    }

    printf("[~] Close GameMenu\n");
}
