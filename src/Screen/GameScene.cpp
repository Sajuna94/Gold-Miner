#include "Screen/GameScene.h"

#include "config.hpp"
#include "Core/LevelManager.h"
#include "Core/ScreenManager.h"
#include "Game/Factory.h"
#include "Screen/PropsShop.h"
#include "Screen/StartMenu.h"
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
        m_FpsTextBox->SetText(fmt::format("{:.2f}", fps));

        // Game Over
        if (m_Logic->GetState() == Game::Logic::State::GAME_OVER) {
            if (const auto level = LevelManager::CreateLevel(LevelManager::GetLevelIndex()); m_ElapsedMoney >= level->GetTargetMoney())
                ToPropsShop(m_ElapsedMoney);
            else {
                ScreenManager::NextScreen(std::make_unique<StartMenu>());
            }
        }

        // F to Shop
        if (Util::Input::IsKeyDown(Util::Keycode::F) && m_Logic->GetMoney() ) {
            if (const auto level = LevelManager::CreateLevel(LevelManager::GetLevelIndex()); m_ElapsedMoney >= level->GetTargetMoney())
                ToPropsShop(m_ElapsedMoney);
        }

        // TAB to Shop
        if (Util::Input::IsKeyDown(Util::Keycode::TAB)) {
            if (LevelManager::GetLevelIndex() == LevelManager::GetMaxLevelIndex())
                ScreenManager::NextScreen(std::make_unique<StartMenu>());
            else
                ToPropsShop(9999);
        }

        // Level Change
        if (Util::Input::IsKeyDown(Util::Keycode::LEFT)) {
            LevelManager::SetLevelIndex(LevelManager::GetLevelIndex() - 1);
            RefreshLevel(LevelManager::GetLevelIndex());
        } else if (Util::Input::IsKeyDown(Util::Keycode::RIGHT)) {
            LevelManager::SetLevelIndex(LevelManager::GetLevelIndex() + 1);
            RefreshLevel(LevelManager::GetLevelIndex());
        }

        // Reset Level
        if (Util::Input::IsKeyPressed(Util::Keycode::LCTRL) && Util::Input::IsKeyDown(Util::Keycode::R)) {
            RefreshLevel(LevelManager::GetLevelIndex());
        }

        if (Util::Input::IsKeyDown(Util::Keycode::P)) {
            if (m_Logic->GetState() == Game::Logic::State::PAUSED)
                m_Logic->Resume();
            else
                m_Logic->Pause();
        }

        // Got Money
        if (m_ElapsedMoney != m_Logic->GetMoney()) {
            m_ElapsedMoney = m_Logic->GetMoney();
            m_MoneySound->Play();
            m_MoneyTextBox->SetText(std::to_string(m_ElapsedMoney));
        }
        if (m_ElapsedTime != m_Logic->GetTime()) {
            m_ElapsedTime = m_Logic->GetTime();
            m_TimeTextBox->SetText(std::to_string(m_ElapsedTime));
        }

        m_Logic->Update(dt);
    }

    void GameScene::Init(Util::Renderer &m_Root) {
        m_MoneySound = std::make_shared<Util::SFX>(RESOURCE_DIR "/Sounds/ring-effect.mp3");

        m_UI = std::make_shared<Util::GameObject>();
        m_Logic = std::make_shared<Game::Logic>();
        m_Root.AddChildren({m_UI, m_Logic});
        MakeUI();

        m_Logic->SetInventory(m_Inventory);
        RefreshLevel(LevelManager::GetLevelIndex());
        m_Logic->Resume();
    }

    void GameScene::ShutDown(Util::Renderer &m_Root) {
        m_Root.RemoveChild(m_UI);
        m_Root.RemoveChild(m_Logic);
    }

    void GameScene::MakeUI() {
        const auto background = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Background/game_background.png");
        background->FullScreen();

        // FPS
        m_FpsTextBox = std::make_shared<UI::TextBox>(
            30, "FPSTextBox", UI::TextBox::Align::RIGHT, UI::TextBox::Style::Sans);
        m_FpsTextBox->SetPosition(
            glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f * 0.95f + glm::vec2(30, 0));

        // Banner
        const auto moneyGoalBanner = std::make_shared<UI::Picture>(
            RESOURCE_DIR "/Textures/Picture/goal-money-banner-night.png");
        moneyGoalBanner->AlignTo(UI::Picture::Align::TOP_LEFT, {40, -40});

        const auto levelTimeBanner = std::make_shared<UI::Picture>(
            RESOURCE_DIR "/Textures/Picture/level-time-banner-night.png");
        levelTimeBanner->AlignTo(UI::Picture::Align::TOP_RIGHT, {-40, 0});

        m_MoneyTextBox = std::make_shared<UI::TextBox>(34, "MoneyTextBox", UI::TextBox::Align::LEFT);
        m_GoalTextBox = std::make_shared<UI::TextBox>(34, "GoalTextBox", UI::TextBox::Align::LEFT);
        m_LevelTextBox = std::make_shared<UI::TextBox>(34, "LevelTextBox", UI::TextBox::Align::LEFT);
        m_TimeTextBox = std::make_shared<UI::TextBox>(34, "TimeTextBox", UI::TextBox::Align::LEFT);

        m_MoneyTextBox->SetPosition(moneyGoalBanner->GetPosition() + glm::vec2(-15, 48));
        m_GoalTextBox->SetPosition(moneyGoalBanner->GetPosition() + glm::vec2(-15, -10));
        m_LevelTextBox->SetPosition(levelTimeBanner->GetPosition() + glm::vec2(0, 15));
        m_TimeTextBox->SetPosition(levelTimeBanner->GetPosition() + glm::vec2(0, -40));

        // Add UI Chile
        std::vector<std::shared_ptr<Util::GameObject> > elements = {
            background, moneyGoalBanner, levelTimeBanner,
            m_FpsTextBox, m_MoneyTextBox, m_GoalTextBox, m_LevelTextBox, m_TimeTextBox
        };
        for (const auto &child: elements) {
            m_UI->AddChild(child);
            child->SetZIndex(5);

            if (const auto &tb = std::dynamic_pointer_cast<UI::TextBox>(child)) {
                tb->SetZIndex(30);
                tb->SetColor(Util::Color::FromRGB(111, 52, 9));
            }
        }
        background->SetZIndex(-5);
        m_FpsTextBox->SetColor(Util::Color::FromName(Util::Colors::RED));
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

    void GameScene::RefreshLevel(const int levelIndex) {
        m_Logic->Load(levelIndex);
        const auto level = LevelManager::CreateLevel(LevelManager::GetLevelIndex());

        m_ElapsedMoney = m_Logic->GetMoney();
        m_ElapsedTime = m_Logic->GetTime();

        m_MoneyTextBox->SetText(std::to_string(m_Logic->GetMoney()));
        m_GoalTextBox->SetText(std::to_string(level->GetTargetMoney()));
        m_LevelTextBox->SetText(std::to_string(LevelManager::GetLevelIndex()));
        m_TimeTextBox->SetText(std::to_string(level->GetTimeLimit()));
    }

    void GameScene::ToPropsShop(const int money) {
        auto next = std::make_unique<PropsShop>();
        next->SetMoney(money);
        ScreenManager::NextScreen(std::move(next));
    }

} // Screen
