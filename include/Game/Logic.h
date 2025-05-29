#ifndef LOGIC_H
#define LOGIC_H
#include <unordered_set>

#include "Level.h"
#include "Spawner.h"
#include "Entity/Bomb.h"
#include "Entity/Miner.h"
#include "Util/GameObject.hpp"

namespace Game {
    class Logic final : public Util::GameObject {
    public:
        enum class State {
            RUNNING,
            PAUSED,
        };

        explicit Logic();

        void Update(float dt);

        void Load(int levelIndex);

        void Reset();

        void Resume();

        void Pause();

        void SetInventory(std::unordered_map<std::string, int> inventory) { m_Inventory = std::move(inventory); }

    private:
        State m_State = State::PAUSED;

        std::shared_ptr<Level> m_Level;
        std::unordered_map<std::string, int> m_Inventory;

        std::shared_ptr<Miner> m_Miner;
        std::shared_ptr<Spawner> m_Spawner;

        std::unordered_set<std::shared_ptr<Bomb> > m_ActiveBombs;
        std::unordered_set<std::shared_ptr<Entity> > m_ActiveTnts;

        void HandleMinerState(float dt);

        void UpdateActiveBombs();
        void UpdateActiveTnts(float dt);
    };
} // Game

#endif //LOGIC_H
