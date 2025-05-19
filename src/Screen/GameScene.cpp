#include "Screen/GameScene.h"

#include <iomanip>

#include "config.hpp"
#include "Game/Factory.h"
#include "UI/Picture.h"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

namespace Position {
    constexpr glm::vec2 targetMoneyTextBox = {0, 0};
}

namespace Screen {
    GameScene::GameScene() {
    }

    void GameScene::Update() {
        const float dt = Util::Time::GetDeltaTimeMs();
        // 60.5
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << (1.0f / dt * 1000.0f);
        m_FPSTextBox->SetText(oss.str());

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
                    m_Miner->ReturnHook();
                if (!m_Hook->GetGlobalHitBox().intersect(rect({WINDOW_WIDTH, WINDOW_HEIGHT})))
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
                        m_UI->RemoveChild(collection);
                    }
                    break;
                }
                m_Hook->Advance(dt);
                break;
        }
    }

    void GameScene::Init(Util::Renderer &m_Root) {
        m_UI = std::make_shared<Util::GameObject>();
        m_Root.AddChild(m_UI);

        m_Miner = std::make_shared<Miner>(50);
        m_Miner->SetPosition({0, 250});
        m_Hook = m_Miner->GetHook();
        m_Root.AddChild(m_Miner);


        m_Entities.emplace(Game::Factory::CreateDiamond());
        for (const auto &entity: m_Entities) {
            entity->SetZIndex(10);
            m_UI->AddChild(entity);
        }

        MakeUI();
    }

    void GameScene::ShutDown(Util::Renderer &m_Root) {
        m_Root.RemoveChild(m_UI);
    }

    void GameScene::MakeUI() {
        const auto background = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Background/game.png");
        background->FullScreen();
        m_UI->AddChild(background);

        m_FPSTextBox = std::make_shared<UI::TextBox>(30, "FPSTextBox", UI::TextBox::Align::MIDDLE,
                                                     RESOURCE_DIR "/Font/samsung-sans-4/SamsungSans-Medium.ttf");
        m_FPSTextBox->m_Transform.translation = glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f * 0.90f;
        m_FPSTextBox->SetColor(Util::Color::FromName(Util::Colors::RED));
        m_FPSTextBox->SetZIndex(30);
        m_UI->AddChild(m_FPSTextBox);
    }
} // Screen
