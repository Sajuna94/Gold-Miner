#ifndef SPAWNER_H
#define SPAWNER_H
#include <queue>

#include "Core/Entity.h"

namespace Game {
    class Spawner final {
    public:
        explicit Spawner(const rect &area);

        ~Spawner() = default;

        std::shared_ptr<Entity> TryEnqueueAndSpawn(const std::shared_ptr<Entity> &entity = nullptr);

        [[nodiscard]] std::vector<std::shared_ptr<Entity> > &GetSpawnedEntities() { return m_SpawnedEntities; }

        void Despawn(const std::shared_ptr<Entity>& entity);

        void Clear();

    private:
        rect m_SpawnArea;
        std::vector<std::shared_ptr<Entity> > m_SpawnedEntities;
        std::queue<std::shared_ptr<Entity> > m_PendingSpawnQueue;

        bool TryPlaceSafePosition(const std::shared_ptr<Entity> &entity) const;
    };
} // Game

#endif //SPAWNER_H
