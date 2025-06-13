#include "Game/Logic.h"

#include <thread>

#include "Core/LevelManager.h"
#include "Core/Timer.h"
#include "Entity/Bomb.h"
#include "Game/Factory.h"
#include "Game/Level.h"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

#define SPAWN_LIMIT 15

namespace Game {
    Logic::Logic() {
        m_Miner = std::make_shared<Miner>(50);
        m_Miner->SetPosition({0, 258});
        AddChild(m_Miner);

        m_Spawner = std::make_shared<Spawner>(rect({0, -110}, {WINDOW_WIDTH, WINDOW_HEIGHT - 220}));
        m_Timer = std::make_shared<Timer>();
    }

    void Logic::Update(const float dt) {
        HandleGameState();

        if (m_State == State::RUNNING) {
            m_Timer->Update(dt);
            HandleMinerState(dt);
            HandlePropsInput();
            UpdateActiveBombs();
            UpdateActiveTnts(dt);
            for (auto &rat: m_ActiveRats) rat->Update(dt);
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
        m_Timer->Reset();
        m_Miner->Reset();
        m_Miner->SetPosition({0, 258});

        m_CurrentMoney = 0;
        m_CurrentSecond = m_Level->GetTimeLimit();

        for (const auto &entity: m_Spawner->GetSpawnedEntities())
            RemoveChild(entity);
        m_Spawner->Clear();
        m_Spawner->SetSpawnLimits(m_Level->GetSpawnLimits());

        m_ActiveBombs.clear();
        m_ActiveTnts.clear();
        m_ActiveRats.clear();

        const auto start = Util::Time::GetElapsedTimeMs();
        while (m_Spawner->GetSpawnedEntities().size() < SPAWN_LIMIT && m_Spawner->GetLimitTotal() != 0) {
            SpawnEntity();
        }
        printf("Created %lld entities in %.2f ms\n", m_Spawner->GetSpawnedEntities().size(),
               Util::Time::GetElapsedTimeMs() - start);
    }

    void Logic::HandleGameState() {
        if (m_Timer->Event(1000)) {
            if (m_State != State::GAME_OVER && --m_CurrentSecond == 0) {
                m_State = State::GAME_OVER;
            }
            if (m_Spawner->GetSpawnedEntities().size() < SPAWN_LIMIT && m_Miner->GetHook()->GetState() ==
                Hook::State::STOPPED) {
                SpawnEntity();
                }
        }
    }

    void Logic::HandleMinerState(const float dt) {
        switch (const auto &hook = m_Miner->GetHook(); hook->GetState()) {
            case Hook::State::STOPPED: {
                if (LevelManager::GetLevelIndex() > 5) {
                    int dir = 0;
                    if (Util::Input::IsKeyPressed(Util::Keycode::A)) dir -= 1;
                    if (Util::Input::IsKeyPressed(Util::Keycode::D)) dir += 1;
                    if (abs(m_Miner->GetPosition().x) > 400) {
                        m_Miner->SetPosition({
                            glm::clamp(m_Miner->GetPosition().x, -400.0f, 400.0f), m_Miner->GetPosition().y
                        });
                    }
                    m_Miner->SmoothMove(dir, dt);
                }

                if (Util::Input::IsKeyDown(Util::Keycode::SPACE) || Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB))
                    m_Miner->ThrowHook();
                if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB))
                    hook->m_Transform.rotation = glm::radians(
                        GetAngleFromTo(hook->GetPosition(), Util::Input::GetCursorPosition()));
                else
                    hook->Swing(dt);
                break;
            }
            case Hook::State::THROWN: {
                if (Util::Input::IsKeyDown(Util::Keycode::SPACE) || Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB))
                    m_Miner->ReturnHook();
                if (!hit::intersect(hook->GetWorldHitBox(), rect({WINDOW_WIDTH, WINDOW_HEIGHT})))
                    m_Miner->ReturnHook();

                for (const auto &entity: m_Spawner->GetSpawnedEntities()) {
                    if (hook->IsOverlay(entity)) {
                        if (const auto &collection = std::dynamic_pointer_cast<Collection>(entity)) {
                            hook->HookCollection(collection);
                            if (collection->GetName() == "Rat") {
                                m_ActiveRats.erase(std::dynamic_pointer_cast<Rat>(collection));
                            }
                        }
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
                        m_CurrentMoney += collection->GetMoney();

                        RemoveChild(collection);
                        hook->ReleaseCollection();
                    }
                    break;
                }
                hook->Advance(dt);
                break;
        }
    }

    void Logic::HandlePropsInput() {
        if (Util::Input::IsKeyDown(Util::Keycode::Q) && m_Inventory["Tnt"] > 0) {
            m_Inventory["Tnt"]--;
            auto tnt = Factory::CreateTnt(70);
            tnt->SetPosition(m_Miner->GetPosition() + glm::vec2(0, -50.0f));
            AddChild(tnt);
            m_ActiveTnts.emplace(tnt);
        }
    }

    void Logic::UpdateActiveBombs() {
        const auto tmpActiveBombs = m_ActiveBombs;
        for (const auto &bomb: tmpActiveBombs) {
            if (!bomb->HasExploded())
                continue;

            std::vector<std::shared_ptr<Entity> > toDespawn;
            for (const auto &entity: m_Spawner->GetSpawnedEntities()) {
                if (bomb->InBlastRadius(entity))
                    toDespawn.emplace_back(entity);
            }
            for (const auto &entity: toDespawn) {
                if (auto other = std::dynamic_pointer_cast<Bomb>(entity)) {
                    other->Explode();
                    m_ActiveBombs.emplace(other);
                } else if (auto rat = std::dynamic_pointer_cast<Rat>(entity)) {
                    RemoveChild(rat);
                    auto diamond = Factory::CreateDiamond(rat->GetZIndex());
                    diamond->SetPosition(rat->GetPosition());
                    m_Spawner->AddSpawned(diamond);
                    AddChild(diamond);
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

            if (!hit::intersect(tnt->GetWorldHitBox(), rect({WINDOW_WIDTH, WINDOW_HEIGHT}))) {
                RemoveChild(tnt);
                m_ActiveTnts.erase(tnt);
                continue;
            }

            std::vector<std::shared_ptr<Entity> > toDespawn;
            for (const auto &entity: m_Spawner->GetSpawnedEntities()) {
                if (entity->GetName() == "Rock" && tnt->IsOverlay(entity)) {
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

    float Logic::GetAngleFromTo(const glm::vec2 &from, const glm::vec2 &to) {
        const glm::vec2 delta = to - from;
        auto angle = static_cast<float>(std::atan2(delta.x, -delta.y) * 180.0 / M_PI);
        if (angle < 0.0f) angle += 360.0f;
        return angle;
    }

    void Logic::SetInventory(const std::unordered_map<std::string, int> &inventory) {
        m_Inventory = inventory;

        if (m_Inventory["StrengthDrink"] >= 1) {
            m_Miner->IncreasesPower();
        }
    }

    void Logic::SpawnEntity() {
        if (const auto &entity = m_Spawner->TrySpawn()) {
            AddChild(entity);
            if (entity->GetName() == "Rat") {
                m_ActiveRats.emplace(std::dynamic_pointer_cast<Rat>(entity));
            }

            if (m_Inventory["DiamondPolish"] >= 1 && entity->GetName() == "Diamond") {
                const auto collection = std::dynamic_pointer_cast<Collection>(entity);
                collection->SetMoney(static_cast<int>(static_cast<float>(collection->GetMoney()) * 1.5f));
            } else if (m_Inventory["StoneBook"] >= 1 && entity->GetName() == "Stone") {
                const auto collection = std::dynamic_pointer_cast<Collection>(entity);
                collection->SetWeight(collection->GetWeight() * 0.5f);
            }
        }
    }
} // Game
