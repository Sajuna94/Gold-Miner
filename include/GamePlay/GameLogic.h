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
    // Current game state.
    State m_GameState = State::PAUSED;

    // Command and entity buffers. PS: Game Adapter
    std::vector<CommandType> m_CommandBuffer; // Store commands to execute.
    std::vector<std::shared_ptr<Util::GameObject>> m_AddableBuffer; // Store addable objectives.
    std::vector<std::shared_ptr<Util::GameObject>> m_RemovableBuffer; // Store removable objectives.

    // Entity control.
    std::shared_ptr<EntitySpawner> m_EntitySpawner; // Entity spawner for handling entities.
    std::unordered_set<std::shared_ptr<Entity>> m_HandleEntityList; // List of entities to update.

    // Timer and time management.
    std::shared_ptr<Timer> m_Timer;
    int m_TimeLeft{}, m_TimeSpawn{};

    //
    std::shared_ptr<Miner> m_Miner;
    int m_Money{};

public:
    // Game state control
    void GameStart();
    void Update(float dt, const InputState& input);
    void GameOver();

    // Extract buffers
    std::vector<CommandType> ExtractCommands();
    std::vector<std::shared_ptr<Util::GameObject>> ExtractAddedChildren();
    std::vector<std::shared_ptr<Util::GameObject>> ExtractRemovedChildren();

    // Getter
    [[nodiscard]] int GetMoney() const { return m_Money; }
    [[nodiscard]] State GetState() const { return m_GameState; }
    [[nodiscard]] int GetTimeLeft() const { return m_TimeLeft; }

private:
    /**
     * @brief Handle game progression, such as win/loss conditions.
     */
    void HandleGameCycle(float dt);

    /**
      * @brief Try to spawn new entities if the timing is right.
      */
    void HandleEntitySpawn();

    /**
     * @brief Update all entities in the game.
     */
    void HandleEntityCycle();

    /**
     * @brief Trigger bomb chain explosion effects.
     */
    void HandleBombExplosion(const std::shared_ptr<Bomb>& bomb);

    /**
     * @brief Update miner's behavior based on input.
     */
    void HandleMinerState(float dt, const InputState& input);
};


#endif //GAMELOGIC_H
