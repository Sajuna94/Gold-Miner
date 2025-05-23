#ifndef LOGIC_H
#define LOGIC_H
#include <unordered_set>

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

        void Load(int level);

        void Reset();

        void Resume();

        void Pause();

    private:
        State m_State = State::PAUSED;

        std::shared_ptr<Miner> m_Miner;
        std::shared_ptr<Spawner> m_Spawner;

        std::unordered_set<std::shared_ptr<Bomb>> m_ActiveBombs;

        void HandleMinerState(float dt);

        void UpdateActiveBombs();
    };
} // Game

#endif //LOGIC_H
