#include "Game/Logic.h"

#include "Game/Factory.h"
#include "Util/Input.hpp"

namespace Game {
    Logic::Logic() {
        m_Miner = std::make_shared<Miner>(50);
        m_Miner->SetPosition({0, 258});
        AddChild(m_Miner);

        m_Spawner = std::make_shared<Spawner>(rect({0, -110}, {WINDOW_WIDTH, WINDOW_HEIGHT - 220}));
    }

    void Logic::Load(int level) {
        Reset();
    }

    void Logic::Update(const float dt) {
        switch (m_State) {
            case State::RUNNING:
                HandleMiner(dt);
                break;
            case State::PAUSED:
                break;
        }
    }

    void Logic::Resume() {
        m_State = State::RUNNING;
    }

    void Logic::Pause() {
        m_State = State::PAUSED;
    }

    void Logic::Reset() {
        // Reset Spawner
        for (const auto &entity: m_Spawner->GetSpawnedEntities())
            RemoveChild(entity);
        m_Spawner->Clear();
        while (m_Spawner->GetSpawnedEntities().size() < 20) {
            if (const auto &entity = m_Spawner->TryEnqueueAndSpawn(Factory::CreateDiamond(10)))
                AddChild(entity);
        }
        //
        Logger::Flush();
    }

    void Logic::HandleMiner(const float dt) const {
        switch (const auto &hook = m_Miner->GetHook(); hook->GetState()) {
            case Hook::State::STOPPED: {
                if (Util::Input::IsKeyDown(Util::Keycode::SPACE))
                    m_Miner->ThrowHook();

                int dir = 0;
                if (Util::Input::IsKeyPressed(Util::Keycode::A)) dir -= 1;
                if (Util::Input::IsKeyPressed(Util::Keycode::D)) dir += 1;
                m_Miner->SmoothMove(dir, dt);

                hook->Swing(dt);
                break;
            }
            case Hook::State::THROWN: {
                if (Util::Input::IsKeyDown(Util::Keycode::SPACE))
                    m_Miner->ReturnHook();
                if (!hit::intersect(hook->GetWorldHitBox(), rect({WINDOW_WIDTH, WINDOW_HEIGHT})))
                    m_Miner->ReturnHook();

                for (const auto &entity: m_Spawner->GetSpawnedEntities()) {
                    if (hook->IsOverlay(entity)) {
                        if (const auto &collection = std::dynamic_pointer_cast<Collection>(entity))
                            hook->HookCollection(collection);
                        m_Miner->ReturnHook();
                        break;
                    }
                }
                hook->Advance(dt);
                break;
            }
            case Hook::State::RETURN:
                if (hook->HasReturned()) {
                    m_Miner->StopHook();

                    if (const auto &collection = hook->GetHookedCollection()) {
                        m_Spawner->Despawn(collection);
                        hook->RemoveChild(collection);
                    }
                    break;
                }
                hook->Advance(dt);
                break;
        }
    }
} // Game
