#include "Game/Logic.h"

#include "Entity/Bomb.h"
#include "Game/Factory.h"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

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
                HandleMinerState(dt);
                UpdateActiveBombs();
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
        // reset spawner
        for (const auto &entity: m_Spawner->GetSpawnedEntities())
            RemoveChild(entity);
        m_Spawner->Clear();
        Logger::Flush();

        const auto time = Util::Time::GetElapsedTimeMs();
        while (m_Spawner->GetSpawnedEntities().size() < 10) {
            if (const auto &entity = m_Spawner->TryEnqueueAndSpawn(Factory::CreateBomb(10)))
                AddChild(entity);
        }
        while (m_Spawner->GetSpawnedEntities().size() < 25) {
            if (const auto &entity = m_Spawner->TryEnqueueAndSpawn(Factory::CreateRandomEntity(10)))
                AddChild(entity);
        }
        printf("Created %d entities in %.2f ms\n", 25, Util::Time::GetElapsedTimeMs() - time);
    }

    void Logic::HandleMinerState(const float dt) {
        switch (const auto &hook = m_Miner->GetHook(); hook->GetState()) {
            case Hook::State::STOPPED: {
                int dir = 0;
                if (Util::Input::IsKeyPressed(Util::Keycode::A)) dir -= 1;
                if (Util::Input::IsKeyPressed(Util::Keycode::D)) dir += 1;
                m_Miner->SmoothMove(dir, dt);

                if (Util::Input::IsKeyDown(Util::Keycode::SPACE))
                    m_Miner->ThrowHook();

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
                        if (const auto &bomb = std::dynamic_pointer_cast<Bomb>(entity)) {
                            bomb->Explode();
                            m_Spawner->Despawn(bomb);
                            m_ActiveBombs.emplace(bomb);
                        }
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
                        RemoveChild(collection);
                        hook->ReleaseCollection();
                    }
                    break;
                }
                hook->Advance(dt);
                break;
        }
    }

    void Logic::UpdateActiveBombs() {
        const auto tmpActiveBombs = m_ActiveBombs;
        for (const auto &bomb: tmpActiveBombs) {
            if (!bomb->HasExploded())
                continue;

            std::vector<std::shared_ptr<Entity> > toDespawn;
            for (const auto &entity: m_Spawner->GetSpawnedEntities()) {
                if (entity->GetName() == "Rock")
                    continue;
                if (bomb->InBlastRadius(entity))
                    toDespawn.emplace_back(entity);
            }
            for (const auto &entity: toDespawn) {
                if (auto other = std::dynamic_pointer_cast<Bomb>(entity)) {
                    other->Explode();
                    m_ActiveBombs.emplace(other);
                } else {
                    RemoveChild(entity);
                }
                m_Spawner->Despawn(entity);
            }
            m_ActiveBombs.erase(bomb);
            RemoveChild(bomb);
        }
    }
} // Game
