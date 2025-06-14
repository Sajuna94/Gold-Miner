#include "Screen/StartMenu.h"

#include "Core/LevelManager.h"
#include "Core/ScreenManager.h"
#include "Screen/GameScene.h"
#include "Util/Input.hpp"


namespace Screen {
    void StartMenu::Update() {
        m_StartButton->SetImage(
            m_StartButton->OnHover()
                ? RESOURCE_DIR "/Textures/Button/start-button-hover.png"
                : RESOURCE_DIR "/Textures/Button/start-button-normal.png"
        );
        if (m_StartButton->OnClick()) {
            LevelManager::SetLevelIndex(1);
            ScreenManager::NextScreen(std::make_unique<GameScene>());
        }

        if (Util::Input::IsKeyDown(Util::Keycode::TAB)) {
            LevelManager::SetLevelIndex(1);
            ScreenManager::NextScreen(std::make_unique<GameScene>());
        }
    }

    void StartMenu::Init(Util::Renderer &m_Root) {
        m_UI = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Background/start.png");
        m_UI->FullScreen();
        m_UI->SetZIndex(-5);
        m_Root.AddChild(m_UI);

        const auto goldMinerText = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Picture/gold-miner-text.png");
        goldMinerText->m_Transform.translation = {0, 100};
        goldMinerText->SetZIndex(0);
        m_UI->AddChild(goldMinerText);

        m_StartButton = std::make_shared<UI::Button>(RESOURCE_DIR "/Textures/Button/start-button-normal.png");
        m_StartButton->m_Transform.translation = {0, -50};
        m_StartButton->SetZIndex(0);
        m_UI->AddChild(m_StartButton);
    }

    void StartMenu::ShutDown(Util::Renderer &m_Root) {
        m_Root.RemoveChild(m_UI);
    }
} // Screen
