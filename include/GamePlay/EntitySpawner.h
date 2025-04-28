#ifndef ENTITYSPAWNER_H
#define ENTITYSPAWNER_H
#include <queue>
#include <unordered_set>

#include "Core/Entity.h"


class EntitySpawner
{
    std::queue<std::shared_ptr<Entity>> m_EntitySpawnQueue;
    std::unordered_set<std::shared_ptr<Entity>> m_SpawnedEntities;
    std::vector<std::shared_ptr<Util::GameObject>> m_EntitiesBuffer;

public:
    void QueueRandomCollectible(const std::shared_ptr<Entity>& entity = nullptr);
    bool TrySpawnEntities();

    static std::shared_ptr<Entity> GenerateRandomCollectible();

    std::vector<std::shared_ptr<Util::GameObject>> ExtractEntities();
    std::unordered_set<std::shared_ptr<Entity>>& GetSpawnedEntities() { return m_SpawnedEntities; }
};


#endif //ENTITYSPAWNER_H
