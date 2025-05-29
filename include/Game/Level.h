#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <unordered_map>

namespace Game {
    class Level final {
    public:
        Level(int timeLimit, int targetMoney);

        ~Level() = default;

        [[nodiscard]] int GetTimeLimit() const { return m_TimeLimit; }
        [[nodiscard]] int GetTargetMoney() const { return m_TargetMoney; }
        [[nodiscard]] std::unordered_map<std::string, int> GetSpawnLimits() const { return m_SpawnLimits; }

        void SetEntityLimit(const std::string& name, int limit);

        void SetSpawnLimits(std::unordered_map<std::string, int> limits);
    private:
        int m_TimeLimit;
        int m_TargetMoney;
        std::unordered_map<std::string, int> m_SpawnLimits;
    };
} // Game

#endif //LEVEL_H
