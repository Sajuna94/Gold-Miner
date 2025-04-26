#include "GamePlay/GameLogic.h"

#include <locale>

#include "config.hpp"
#include "Collectibles/Bag.h"
#include "Collectibles/Bomb.h"
#include "Collectibles/Diamond.h"
#include "Collectibles/Gold.h"
#include "Collectibles/Rock.h"
#include "Util/Time.hpp"

constexpr int HALF_WINDOW_WIDTH = WINDOW_WIDTH / 2;
constexpr int HALF_WINDOW_HEIGHT = WINDOW_HEIGHT / 2;

#define MAX_COLLECTIBLE_COUNT 25
#define MAX_SPAWN_ATTEMPTS  20

#define PLAY_TIME_LIMIT 60
#define SPAWN_INTERVAL 5


namespace
{
    using EntityFactory = std::function<std::shared_ptr<Entity>()>;

    const std::vector<EntityFactory> kCollectibleFactories = {
        []() { return std::make_shared<Diamond>(10); },
        []() { return std::make_shared<Rock>(10); },
        []() { return std::make_shared<Gold>(10); },
        []() { return std::make_shared<Bag>(10); },
        []() { return std::make_shared<Bomb>(10); }
    };
}


void GameLogic::GameStart()
{
    printf("Starting Game\n");

    m_Timer = std::make_shared<Timer>(0);
    m_TimeLeft = PLAY_TIME_LIMIT;
    m_CommandBuffer.push_back(CommandType::UpdateTimeLeft);

    m_Miner = std::make_shared<Miner>(5, 50);
    m_AddableList.push_back(m_Miner);

    // Push Random Collectible of Queue
    const auto time = Util::Time::GetElapsedTimeMs();
    for (int i = 0; i < MAX_COLLECTIBLE_COUNT; i++)
        m_SpawnQueue.push(CreateRandomCollectible());
    printf("Creating & Loading %d collectible done. %f ms\n", MAX_COLLECTIBLE_COUNT, Util::Time::GetElapsedTimeMs() - time);

    m_State = State::RUNNING;
}

void GameLogic::Update(const float dt, const InputState& input)
{
    switch (m_State)
    {
    case State::RUNNING:
        {
            // Game Trigger
            HandleGameCycle(dt);
            // Place Entities
            TrySpawnEntities();
            // Bomb Chain Explosion
            HandleBombExplosion();
            // Handle Miner & Pickaxe Logic
            HandleMinerState(dt, input);
        }
        break;
    case State::PAUSED:
        break;
    case State::GAME_OVER:
        break;
    }

    // Handle Children Command
    if (!m_AddableList.empty())
        m_CommandBuffer.push_back(CommandType::AddChildren);
    if (!m_RemovableList.empty())
        m_CommandBuffer.push_back(CommandType::RemoveChildren);
}

void GameLogic::GameOver()
{
    m_State = State::GAME_OVER;
}

void GameLogic::HandleGameCycle(const float dt)
{
    m_Timer->Update(dt);
    if (m_Timer->Event())
    {
        // GameOver Trigger
        m_TimeLeft--;
        if (m_TimeLeft <= 0)
            GameOver();
        m_CommandBuffer.push_back(CommandType::UpdateTimeLeft);

        // Push Random Collectible Entity
        m_TimeSpawn++;
        if (m_TimeSpawn % SPAWN_INTERVAL == 0)
        {
            m_SpawnQueue.push(CreateRandomCollectible());
            m_TimeSpawn = 0;
        }
    }
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

        for (const auto& entity : m_PlacedEntityList)
        {
            if (pickaxe->IsOverlay(entity))
            {
                if (const auto& grabbable = std::dynamic_pointer_cast<IGrabbable>(entity))
                    m_Miner->SetGrabItem(grabbable);
                else if (const auto& bomb = std::dynamic_pointer_cast<Bomb>(entity))
                {
                    bomb->Explosion();
                    m_PlacedEntityList.remove(bomb);
                    m_BombHandleList.push_back(bomb);
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
                m_RemovableList.push_back(grabItem);
                m_PlacedEntityList.remove(grabItem);
                m_Money += grabbable->GetMoney();
                m_CommandBuffer.push_back(CommandType::AddMoney);
            }
        }
        break;
    }
}

void GameLogic::HandleBombExplosion()
{
    const auto temp = m_BombHandleList;
    for (const auto& bomb : temp)
    {
        if (!bomb->IsBlownUp())
            continue;

        m_BombHandleList.remove(bomb);
        m_RemovableList.push_back(bomb);

        const auto tempEntityList = m_PlacedEntityList;
        for (const auto& entity : tempEntityList)
        {
            if (bomb->InTheBlowRange(entity))
            {
                m_PlacedEntityList.remove(entity);

                if (const auto& otherBomb = std::dynamic_pointer_cast<Bomb>(entity))
                {
                    if (otherBomb->IsBlownUp())
                        continue;
                    otherBomb->Explosion();
                    m_BombHandleList.push_back(otherBomb);
                }
                else
                    m_RemovableList.push_back(entity);
            }
        }
    }
}

std::shared_ptr<Entity> GameLogic::CreateRandomCollectible()
{
    return kCollectibleFactories[
        RandInRange(0, static_cast<int>(kCollectibleFactories.size()) - 1)
    ]();
}

void GameLogic::TrySpawnEntities()
{


    while (!m_SpawnQueue.empty() && m_PlacedEntityList.size() < MAX_COLLECTIBLE_COUNT)
    {
        std::shared_ptr<Entity> entity = m_SpawnQueue.front();

        const int width = static_cast<int>(WINDOW_WIDTH - entity->GetHitBox().size.x) / 2;
        const int height = static_cast<int>((WINDOW_HEIGHT - entity->GetHitBox().size.y)) / 2;

        int tryPlaceCount = 0;
        while (tryPlaceCount < MAX_SPAWN_ATTEMPTS)
        {
            tryPlaceCount++;

            entity->SetPosition({
                RandInRange(-width, width),
                RandInRange(-height, height - 200)
            });

            if (std::none_of(m_PlacedEntityList.begin(), m_PlacedEntityList.end(),
                             [&](const auto& other) { return other->IsOverlay(entity); }))
            {
                break;
            }
        }
        if (tryPlaceCount < MAX_SPAWN_ATTEMPTS)
        {
            m_AddableList.push_back(entity);
            m_PlacedEntityList.push_back(entity);
            m_SpawnQueue.pop();
        }
    }

}

std::vector<GameLogic::CommandType> GameLogic::ExtractCommands()
{
    return std::exchange(m_CommandBuffer, {});
}

std::vector<std::shared_ptr<Util::GameObject>> GameLogic::ExtractAddedChildren()
{
    return std::exchange(m_AddableList, {});
}

std::vector<std::shared_ptr<Util::GameObject>> GameLogic::ExtractRemovedChildren()
{
    return std::exchange(m_RemovableList, {});
}
