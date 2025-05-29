#include "Game/Level.h"

namespace Game {
    Level::Level(const int timeLimit, const int targetMoney)
        : m_TimeLimit(timeLimit), m_TargetMoney(targetMoney) {
    }

    void Level::SetEntityLimit(const std::string &name, const int limit) {
        m_SpawnLimits[name] = limit;
    }

    void Level::SetSpawnLimits(std::unordered_map<std::string, int> limits) {
        m_SpawnLimits = std::move(limits);
    }
} // Game
