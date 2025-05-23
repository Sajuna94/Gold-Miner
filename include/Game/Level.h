#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <unordered_map>

namespace Game {
    class Level final {
    public:
        Level(int timeLimit, int targetMoney);

        ~Level() = default;

        void Level::SetEntityLimit(const std::string &name, int limit);

        [[nodiscard]] int Level::GetRemaining(const std::string &name) const;

        [[nodiscard]] bool Level::TryConsumeSpawn(const std::string &name);

        [[nodiscard]] int GetTimeLimit() const { return m_TimeLimit; }
        [[nodiscard]] int GetTargetMoney() const { return m_TargetMoney; }

    private:
        int m_TimeLimit;
        int m_TargetMoney;
        int m_TotalSpawnLimit;
        std::unordered_map<std::string, int> m_EntitySpawnLimits;
    };
} // Game

#endif //LEVEL_H
