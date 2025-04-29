#include "GamePlay/GameLogic.h"

#include <locale>

#include "config.hpp"
#include "Collectibles/Bag.h"
#include "Collectibles/Bomb.h"
#include "Util/Time.hpp"

constexpr int HALF_WINDOW_WIDTH = WINDOW_WIDTH / 2;
constexpr int HALF_WINDOW_HEIGHT = WINDOW_HEIGHT / 2;

#define MAX_COLLECTIBLE_COUNT 50

#define PLAY_TIME_LIMIT 60
#define SPAWN_INTERVAL 5

void GameLogic::GameStart()
{
    printf("Starting Game\n");

    m_EntitySpawner = std::make_shared<EntitySpawner>();

    m_Timer = std::make_shared<Timer>(0, 1000);
    m_TimeLeft = PLAY_TIME_LIMIT;
    m_CommandBuffer.push_back(CommandType::UpdateTimeLeft);

    m_Miner = std::make_shared<Miner>(5, 50);
    m_AddableBuffer.push_back(m_Miner);

    // Push Random Collectible of Queue
    const auto time = Util::Time::GetElapsedTimeMs();
    for (int i = 0; i < MAX_COLLECTIBLE_COUNT; i++)
        m_EntitySpawner->QueueRandomCollectible();
    printf("Creating & Loading %d collectible done. %f ms\n", MAX_COLLECTIBLE_COUNT,
           Util::Time::GetElapsedTimeMs() - time);

    m_GameState = State::RUNNING;
}

void GameLogic::Update(const float dt, const InputState& input)
{
    switch (m_GameState)
    {
    case State::RUNNING:
        // Order doesn't matter in this cycle
        HandleGameCycle(dt); // Game Trigger
        HandleEntitySpawn(); // Place Entities
        HandleEntityCycle(); // Bomb Chain Explosion
        HandleMinerState(dt, input); // Handle Miner & Pickaxe Logic
        break;
    case State::PAUSED:
        break;
    case State::GAME_OVER:
        break;
    }

    // Handle Children Command
    if (!m_AddableBuffer.empty())
        m_CommandBuffer.push_back(CommandType::AddChildren);
    if (!m_RemovableBuffer.empty())
        m_CommandBuffer.push_back(CommandType::RemoveChildren);
}

void GameLogic::GameOver()
{
    m_GameState = State::GAME_OVER;
}

void GameLogic::HandleGameCycle(const float dt)
{
    m_Timer->Update(dt);
    if (m_Timer->Event())
    {
        // GameOver Trigger
        if (--m_TimeLeft <= 0)
            GameOver();
        m_CommandBuffer.push_back(CommandType::UpdateTimeLeft);

        // Push Random Collectible Entity
        if (++m_TimeSpawn % SPAWN_INTERVAL == 0)
        {
            m_EntitySpawner->QueueRandomCollectible();
            m_TimeSpawn = 0;
        }
    }
}

void GameLogic::HandleEntitySpawn()
{
    if (m_Miner->GetState() != Miner::State::STOPPED)
        return;
    while (m_EntitySpawner->GetSpawnedEntities().size() < MAX_COLLECTIBLE_COUNT)
    {
        if (!m_EntitySpawner->TrySpawnEntity())
            break;
    }
    for (const auto& entity : m_EntitySpawner->ExtractEntities())
        m_AddableBuffer.push_back(entity);
}

void GameLogic::HandleMinerState(const float dt, const InputState& input)
{
    m_Miner->Update(dt);

    const auto pickaxe = m_Miner->GetPickaxe();
    switch (m_Miner->GetState())
    {
    case Miner::State::STOPPED:
        if (input.MoveLeftMiner)
            m_Miner->Move({-1, 0}, dt);
        if (input.MoveRightMiner)
            m_Miner->Move({1, 0}, dt);
        if (input.ThrowPickaxe)
            m_Miner->ThrowPickaxe();
        break;
    case Miner::State::THROWING:
        if (input.ReturnPickaxe)
            m_Miner->ReturnPickaxe();

        for (const auto& entity : m_EntitySpawner->GetSpawnedEntities())
        {
            if (pickaxe->IsOverlay(entity))
            {
                if (const auto& grabbable = std::dynamic_pointer_cast<IGrabbable>(entity))
                    m_Miner->SetGrabItem(grabbable);
                else if (const auto& bomb = std::dynamic_pointer_cast<Bomb>(entity))
                {
                    bomb->Explosion();
                    m_HandleEntityList.insert(bomb);
                }
                m_Miner->ReturnPickaxe();
                break;
            }
        }
        break;
    case Miner::State::RETURN:

        if (m_Miner->IsReturnBack())
        {
            m_Miner->StopPickaxe();
            if (const auto& grabItem = m_Miner->GetGrabItem())
            {
                const auto grabbable = std::dynamic_pointer_cast<IGrabbable>(grabItem);
                m_RemovableBuffer.push_back(grabItem);
                m_EntitySpawner->GetSpawnedEntities().erase(grabItem);
                m_Money += grabbable->GetMoney();
                m_CommandBuffer.push_back(CommandType::AddMoney);
            }
        }
        break;
    }
}

void GameLogic::HandleEntityCycle()
{
    const auto temp = m_HandleEntityList;
    for (const auto& entity : temp)
    {
        if (const auto& bomb = std::dynamic_pointer_cast<Bomb>(entity))
            HandleBombExplosion(bomb);
    }
}

void GameLogic::HandleBombExplosion(const std::shared_ptr<Bomb>& bomb)
{
    if (!bomb->IsBlownUp())
        return;

    printf("[GameLogic] Bomb handle over\n");

    auto& spawnedEntities = m_EntitySpawner->GetSpawnedEntities();

    spawnedEntities.erase(bomb);
    m_HandleEntityList.erase(bomb);
    m_RemovableBuffer.push_back(bomb);

    std::vector<std::shared_ptr<Entity>> removableEntities;
    for (const auto& entity : spawnedEntities)
        if (bomb->InTheBlowRange(entity))
        {
            if (const auto& otherBomb = std::dynamic_pointer_cast<Bomb>(entity))
            {
                if (otherBomb->IsBlownUp())
                    continue;
                otherBomb->Explosion();
                m_HandleEntityList.insert(otherBomb);
            }
            else
            {
                removableEntities.push_back(entity);
                m_RemovableBuffer.push_back(entity);
            }
        }
    for (const auto& removable : removableEntities)
        spawnedEntities.erase(removable);
}

std::vector<GameLogic::CommandType> GameLogic::ExtractCommands()
{
    return std::exchange(m_CommandBuffer, {});
}

std::vector<std::shared_ptr<Util::GameObject>> GameLogic::ExtractAddedChildren()
{
    return std::exchange(m_AddableBuffer, {});
}

std::vector<std::shared_ptr<Util::GameObject>> GameLogic::ExtractRemovedChildren()
{
    return std::exchange(m_RemovableBuffer, {});
}
