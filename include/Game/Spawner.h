#ifndef SPAWNER_H
#define SPAWNER_H
#include <optional>
#include <queue>
#include <random>

#include "Core/Entity.h"

namespace Game {
    class Spawner final {
    public:
        explicit Spawner(const rect &area);

        ~Spawner() = default;

        void SetSpawnLimits(std::unordered_map<std::string, int> limits);

        [[nodiscard]] std::vector<std::shared_ptr<Entity> > &GetSpawnedEntities() { return m_Spawned; }

        [[nodiscard]] std::shared_ptr<Entity> TrySpawn();

        void Despawn(const std::shared_ptr<Entity> &entity);

        void Clear();

        [[nodiscard]] int GetLimitTotal();

        void AddSpawned(const std::shared_ptr<Entity>& entity);

    private:
        mutable std::mt19937 m_Rng{std::random_device{}()};
        rect m_SpawnArea;
        std::vector<std::shared_ptr<Entity> > m_Spawned;
        std::queue<std::string> m_Pending;
        std::unordered_map<std::string, int> m_SpawnLimits;

        std::optional<std::string> PickSpawnName();

        bool TryPlaceSafe(const std::shared_ptr<Entity> &entity) const;
    };
} // Game

#endif //SPAWNER_H
