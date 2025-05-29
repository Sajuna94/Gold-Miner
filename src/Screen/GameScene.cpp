#include "Screen/GameScene.h"

#include "config.hpp"
#include "Core/LevelManager.h"
#include "Core/ScreenManager.h"
#include "Game/Factory.h"
#include "Screen/PropsShop.h"
#include "UI/Picture.h"
#include "Util/Input.hpp"
#include "Util/Time.hpp"


namespace Position {
    constexpr glm::vec2 targetMoneyTextBox = {0, 0};
}

namespace Screen {
    void GameScene::Update() {
        const float dt = Util::Time::GetDeltaTimeMs();

        // FPS averaged over 60 frames
        float fps = CalculateSmoothedFPS(dt);
        m_FPSTextBox->SetText(fmt::format("{:.2f}", fps));

        // TAB to Shop
        if (Util::Input::IsKeyDown(Util::Keycode::TAB)) {
            auto next = std::make_unique<PropsShop>();
            next->SetMoney(9999);
            ScreenManager::NextScreen(std::move(next));
        }

        // Reset
        if (Util::Input::IsKeyPressed(Util::Keycode::LCTRL) && Util::Input::IsKeyDown(Util::Keycode::R)) {
            m_Logic->Reset();
        }

        m_Logic->Update(dt);
    }

    void GameScene::Init(Util::Renderer &m_Root) {
        m_UI = std::make_shared<Util::GameObject>();
        m_Logic = std::make_shared<Game::Logic>();
        m_Logic->SetInventory(m_Inventory);
        m_Logic->Load(LevelManager::GetLevelIndex());
        m_Logic->Resume();

        m_Root.AddChildren({m_UI, m_Logic});
        MakeUI();
    }

    void GameScene::ShutDown(Util::Renderer &m_Root) {
        m_Root.RemoveChild(m_UI);
        m_Root.RemoveChild(m_Logic);
    }

    void GameScene::MakeUI() {
        const auto background = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Background/game.png");
        background->FullScreen();
        m_UI->AddChild(background);

        // FPS TextBox
        m_FPSTextBox = std::make_shared<UI::TextBox>(30, "FPSTextBox", UI::TextBox::Align::RIGHT,
                                                     RESOURCE_DIR "/Font/samsung-sans-4/SamsungSans-Medium.ttf");
        m_FPSTextBox->m_Transform.translation = glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f * 0.95f;
        m_FPSTextBox->m_Transform.translation.x += 45;
        m_FPSTextBox->SetColor(Util::Color::FromName(Util::Colors::RED));
        m_FPSTextBox->SetZIndex(30);
        m_UI->AddChild(m_FPSTextBox);
    }

    float GameScene::CalculateSmoothedFPS(const float dt) {
        dtQueue.push_back(dt);
        dtSum += dt;

        static constexpr int MAX_FPS_SAMPLES = 60;
        if (dtQueue.size() > MAX_FPS_SAMPLES) {
            dtSum -= dtQueue.front();
            dtQueue.pop_front();
        }

        const float avgDt = dtSum / static_cast<float>(dtQueue.size());
        return 1000.0f / avgDt;
    }
} // Screen
