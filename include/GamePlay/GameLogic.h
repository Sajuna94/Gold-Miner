#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <list>
#include <memory>
#include <queue>

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
    // Game Adapter
    State m_State = State::PAUSED;
    std::vector<CommandType> m_CommandBuffer;

    // Children List
    std::vector<std::shared_ptr<Util::GameObject>> m_AddableList;
    std::vector<std::shared_ptr<Util::GameObject>> m_RemovableList;

    // Timer
    std::shared_ptr<Timer> m_Timer;
    int m_TimeLeft{}, m_TimeSpawn{};

    // Spawn Logic
    std::queue<std::shared_ptr<Entity>> m_SpawnQueue;
    std::list<std::shared_ptr<Entity>> m_PlacedEntityList;

    //
    std::list<std::shared_ptr<Bomb>> m_BombHandleList;
    std::shared_ptr<Miner> m_Miner;
    int m_Money{};

public:
    // Control
    void GameStart();
    void Update(float dt, const InputState& input);
    void GameOver();

    // Extract
    std::vector<CommandType> ExtractCommands();
    std::vector<std::shared_ptr<Util::GameObject>> ExtractAddedChildren();
    std::vector<std::shared_ptr<Util::GameObject>> ExtractRemovedChildren();

    // Getter
    [[nodiscard]] int GetMoney() const { return m_Money; }
    [[nodiscard]] State GetState() const { return m_State; }
    [[nodiscard]] int GetTimeLeft() const { return m_TimeLeft; }

private:
    void TrySpawnEntities();
    static std::shared_ptr<Entity> CreateRandomCollectible();

    void HandleGameCycle(float dt);
    void HandleBombExplosion();
    void HandleMinerState(float dt, const InputState& input);
};


#endif //GAMELOGIC_H
