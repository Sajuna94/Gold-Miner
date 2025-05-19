#include "Screen/GameScene.h"

#include "config.hpp"
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
            ScreenManager::NextScreen(std::make_unique<PropsShop>());
        }

        switch (m_Hook->GetState()) {
            case Hook::State::STOPPED: {
                if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
                    m_Miner->ThrowHook();
                    break;
                }

                int dir = 0;
                if (Util::Input::IsKeyPressed(Util::Keycode::A)) dir -= 1;
                if (Util::Input::IsKeyPressed(Util::Keycode::D)) dir += 1;
                m_Miner->Move(dir, dt);

                m_Hook->Swing(dt);
            }
            break;
            case Hook::State::THROWN: {
                if (Util::Input::IsKeyDown(Util::Keycode::SPACE))
                    m_Miner->ReturnHook();;
                if (!hit::intersect(m_Hook->GetWorldHitBox(), rect({WINDOW_WIDTH, WINDOW_HEIGHT})))
                    m_Miner->ReturnHook();

                for (const auto &entity: m_Entities) {
                    if (m_Hook->IsOverlay(entity)) {
                        if (const auto &collection = std::dynamic_pointer_cast<Collection>(entity))
                            m_Hook->HookCollection(collection);
                        m_Miner->ReturnHook();
                        break;
                    }
                }
                m_Hook->Advance(dt);
            }
            break;
            case Hook::State::RETURN:
                if (m_Hook->HasReturned()) {
                    m_Miner->StopHook();

                    if (const auto &collection = m_Hook->GetHookedCollection()) {
                        m_Entities.erase(collection);
                        m_Game->RemoveChild(collection);
                    }
                    break;
                }
                m_Hook->Advance(dt);
                break;
        }
    }

    void GameScene::Init(Util::Renderer &m_Root) {
        m_UI = std::make_shared<Util::GameObject>();
        m_Game = std::make_shared<Util::GameObject>();
        m_Root.AddChildren({m_UI, m_Game});

        m_Miner = std::make_shared<Miner>(50);
        m_Miner->SetPosition({0, 258});
        m_Hook = m_Miner->GetHook();
        m_Game->AddChild(m_Miner);


        m_Entities.emplace(Game::Factory::CreateDiamond());
        m_Entities.emplace(Game::Factory::CreateDiamond());
        m_Entities.emplace(Game::Factory::CreateDiamond());
        m_Entities.emplace(Game::Factory::CreateDiamond());
        m_Entities.emplace(Game::Factory::CreateDiamond());
        m_Entities.emplace(Game::Factory::CreateDiamond());
        m_Entities.emplace(Game::Factory::CreateDiamond());

        for (const auto &entity: m_Entities) {
            entity->SetZIndex(10);
            m_Game->AddChild(entity);
        }

        MakeUI();
    }

    void GameScene::ShutDown(Util::Renderer &m_Root) {
        m_Root.RemoveChild(m_UI);
        m_Root.RemoveChild(m_Game);
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
