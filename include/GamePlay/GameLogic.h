#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <memory>
#include <unordered_set>

#include "EntitySpawner.h"
#include "Miner.h"
#include "Core/Entity.h"
#include "Timer.h"
#include "Collectibles/Bomb.h"

struct InputState
{
    bool MoveLeftMiner = false;
    bool MoveRightMiner = false;
    bool ThrowPickaxe = false;
    bool ReturnPickaxe = false;
};

class GameLogic
{
public:
    enum class State
    {
        RUNNING,
        PAUSED,
        GAME_OVER,
    };

    enum class CommandType
    {
        AddChildren,
        RemoveChildren,
        AddMoney,
        UpdateTimeLeft,
    };

private:
    State m_GameState = State::PAUSED;

    // Game Adapter
    std::vector<CommandType> m_CommandBuffer;
    std::vector<std::shared_ptr<Util::GameObject>> m_AddableBuffer;
    std::vector<std::shared_ptr<Util::GameObject>> m_RemovableBuffer;

    // Entity Control
    std::shared_ptr<EntitySpawner> m_EntitySpawner;
    std::unordered_set<std::shared_ptr<Entity>> m_HandleEntityList;

    // Timer
    std::shared_ptr<Timer> m_Timer;
    int m_TimeLeft{}, m_TimeSpawn{};

    //
    std::shared_ptr<Miner> m_Miner;
    int m_Money{};

public:
    // Game State Control
    void GameStart();
    void Update(float dt, const InputState& input);
    void GameOver();

    // Extract Buffer
    std::vector<CommandType> ExtractCommands();
    std::vector<std::shared_ptr<Util::GameObject>> ExtractAddedChildren();
    std::vector<std::shared_ptr<Util::GameObject>> ExtractRemovedChildren();

    // Getter
    [[nodiscard]] int GetMoney() const { return m_Money; }
    [[nodiscard]] State GetState() const { return m_GameState; }
    [[nodiscard]] int GetTimeLeft() const { return m_TimeLeft; }

private:
    // Handle Game State
    void HandleGameCycle(float dt);

    // Spawn Logic
    void HandleEntitySpawn();

    // Entity Update Unit
    void HandleEntityCycle();
    void HandleBombExplosion(const std::shared_ptr<Bomb>& bomb);

    // Miner Update Logic
    void HandleMinerState(float dt, const InputState& input);
};


#endif //GAMELOGIC_H
