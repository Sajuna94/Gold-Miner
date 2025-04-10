//
// Created by ianli_7p249vy on 2025/3/28.
//

#include "Menu.h"

Menu::Menu(Util::Renderer *m_Root) {
    m_startButton = std::make_shared<Button>(RESOURCE_DIR"/gold_miner_source/button-sheet0.png");
    m_startButton->SetPosition({0.5f, 0.5f});

    m_Root->AddChild(m_startButton);
}

void Menu::Update() {
    if (m_startButton->CheckClick()) {
        printf("Click Button! start menu -> start button");


    }

}

