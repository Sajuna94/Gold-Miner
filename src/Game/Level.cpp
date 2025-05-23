#include "Game/Level.h"

namespace Game {
    Level::Level(const int timeLimit, const int targetMoney)
        : m_TimeLimit(timeLimit), m_TargetMoney(targetMoney) {
    }

    void Level::SetEntityLimit(const std::string &name, const int limit) {
        m_EntitySpawnLimits[name] = limit;
        m_TotalSpawnLimit += limit;
    }

    int Level::GetRemaining(const std::string &name) const {
        const auto it = m_EntitySpawnLimits.find(name);
        return it != m_EntitySpawnLimits.end() ? it->second : 0;
    }

    bool Level::TryConsumeSpawn(const std::string &name) {
        const auto it = m_EntitySpawnLimits.find(name);

        if (it == m_EntitySpawnLimits.end()) {
            return true;
        }
        if (it->second > 0) {
            --(it->second);
            return true;
        }
        return false;
    }
} // Game
