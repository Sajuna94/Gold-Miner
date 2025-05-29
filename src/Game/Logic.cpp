#include "Game/Logic.h"

#include "Core/LevelManager.h"
#include "Entity/Bomb.h"
#include "Game/Factory.h"
#include "Game/Level.h"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

namespace Game {
    Logic::Logic() {
        m_Miner = std::make_shared<Miner>(50);
        m_Miner->SetPosition({0, 258});
        AddChild(m_Miner);

        m_Spawner = std::make_shared<Spawner>(rect({0, -110}, {WINDOW_WIDTH, WINDOW_HEIGHT - 220}));
    }

    void Logic::Update(const float dt) {
        switch (m_State) {
            case State::RUNNING:
                HandleMinerState(dt);
                UpdateActiveBombs();
                UpdateActiveTnts(dt);
                break;
            case State::PAUSED:
                break;
        }

        if (Util::Input::IsKeyDown(Util::Keycode::Q) && m_Inventory["Tnt"] > 0) {
            m_Inventory["Tnt"]--;
            auto tnt = Factory::CreateTnt(20);
            tnt->SetPosition(m_Miner->GetPosition());
            AddChild(tnt);
            m_ActiveTnts.emplace(tnt);
        }
    }

    void Logic::Resume() {
        m_State = State::RUNNING;
    }

    void Logic::Pause() {
        m_State = State::PAUSED;
    }

    void Logic::Load(const int levelIndex) {
        m_Level = LevelManager::CreateLevel(levelIndex);
        Reset();
    }

    void Logic::Reset() {
        for (const auto &entity: m_Spawner->GetSpawnedEntities())
            RemoveChild(entity);
        m_Spawner->Clear();
        m_Spawner->SetSpawnLimits(m_Level->GetSpawnLimits());

        const auto start = Util::Time::GetElapsedTimeMs();
        while (m_Spawner->GetSpawnedEntities().size() < 10) {
            if (const auto &entity = m_Spawner->TrySpawn())
                AddChild(entity);
        }
        printf("Created %d entities in %.2f ms\n", 10, Util::Time::GetElapsedTimeMs() - start);
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

    void Logic::UpdateActiveTnts(const float dt) {
        const auto tmpActiveBombs = m_ActiveTnts;
        for (const auto &tnt: tmpActiveBombs) {
            tnt->m_Transform.rotation += 0.2f;
            tnt->Move(glm::vec2(0, -0.3f), dt);

            std::vector<std::shared_ptr<Entity> > toDespawn;
            for (const auto &entity: m_Spawner->GetSpawnedEntities()) {
                if (entity->GetName() != "Rock")
                    continue;
                if (tnt->IsOverlay(entity)) {
                    // create explode effect
                    auto bomb = Factory::CreateBomb(tnt->GetZIndex(), 100);
                    bomb->Explode();
                    bomb->SetPosition(tnt->GetPosition());
                    AddChild(bomb);
                    m_ActiveBombs.emplace(bomb);

                    // remove tnt
                    RemoveChild(tnt);
                    m_ActiveTnts.erase(tnt);

                    toDespawn.emplace_back(entity);
                }
            }
            for (const auto &entity: toDespawn) {
                m_Spawner->Despawn(entity);
                RemoveChild(entity);
            }
        }
    }
} // Game
