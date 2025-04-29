#ifndef ENTITYSPAWNER_H
#define ENTITYSPAWNER_H
#include <queue>
#include <unordered_set>

#include "Core/Entity.h"


class EntitySpawner
{
    // Queue for entities that can't be placed yet.
    std::queue<std::shared_ptr<Entity>> m_EntitySpawnQueue;
    // Set of already spawned entities.
    std::unordered_set<std::shared_ptr<Entity>> m_SpawnedEntities;
    // Buffer for newly added entities.
    std::vector<std::shared_ptr<Util::GameObject>> m_EntitiesBuffer;

public:
    /**
     * @brief Queue a random collectible entity.
     */
    void QueueRandomCollectible(const std::shared_ptr<Entity>& entity = nullptr);

    /**
     * @brief Try to spawn an entity.
     * @return True if spawn successful.
     */
    bool TrySpawnEntity();

    /**
     * @brief Generate a random collectible entity.
     */
    static std::shared_ptr<Entity> GenerateRandomCollectible();

    /**
     * @brief Extract entities from the buffer.
     */
    std::vector<std::shared_ptr<Util::GameObject>> ExtractEntities();

    /**
     * @brief Get the set of spawned entities.
     */
    std::unordered_set<std::shared_ptr<Entity>>& GetSpawnedEntities() { return m_SpawnedEntities; }
};


#endif //ENTITYSPAWNER_H
