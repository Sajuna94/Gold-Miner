#ifndef LOGIC_H
#define LOGIC_H
#include "Spawner.h"
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

        void HandleMiner(float dt) const;
    };
} // Game

#endif //LOGIC_H
