#ifndef LOGIC_H
#define LOGIC_H
#include <unordered_set>

#include "Level.h"
#include "Spawner.h"
#include "Core/Timer.h"
#include "Entity/Bomb.h"
#include "Entity/Miner.h"
#include "Entity/Rat.h"
#include "Util/GameObject.hpp"

namespace Game {
    class Logic final : public Util::GameObject {
    public:
        enum class State {
            RUNNING,
            PAUSED,
            GAME_OVER,
        };

        explicit Logic();

        void Update(float dt);

        void Load(int levelIndex);

        void Reset();

        void Resume();

        void Pause();

        void SetInventory(const std::unordered_map<std::string, int> &inventory);


        [[nodiscard]] State GetState() const { return m_State; }
        [[nodiscard]] int GetMoney() const { return m_CurrentMoney; }
        [[nodiscard]] int GetTime() const { return m_CurrentSecond; }

    private:
        State m_State = State::PAUSED;

        std::shared_ptr<Level> m_Level;
        std::unordered_map<std::string, int> m_Inventory;
        int m_CurrentMoney = 0;

        std::shared_ptr<Timer> m_Timer;
        int m_CurrentSecond = 0;

        std::shared_ptr<Miner> m_Miner;
        std::shared_ptr<Spawner> m_Spawner;

        std::unordered_set<std::shared_ptr<Bomb> > m_ActiveBombs;
        std::unordered_set<std::shared_ptr<Entity> > m_ActiveTnts;
        std::unordered_set<std::shared_ptr<Rat> > m_ActiveRats;

        void HandleMinerState(float dt);

        void HandlePropsInput();

        void HandleGameState(float dt);

        void UpdateActiveBombs();

        void UpdateActiveTnts(float dt);

        static float GetAngleFromTo(const glm::vec2 &from, const glm::vec2 &to);

        static int WrapMod(const int a, const int b) {
            return (a % b + b) % b;
        }

        void SpawnEntity();
    };
} // Game

#endif //LOGIC_H
