#include "Game/Spawner.h"

#include <random>


#include "Game/Factory.h"

namespace Game {
    Spawner::Spawner(const rect &area)
        : m_SpawnArea(area) {
    }

    std::shared_ptr<Entity> Spawner::TryEnqueueAndSpawn(const std::shared_ptr<Entity> &entity) {
        m_PendingSpawnQueue.emplace(entity ? entity : Factory::CreateGold(10));
        auto spawned = m_PendingSpawnQueue.front();

        if (!TryPlaceSafePosition(spawned))
            return nullptr;

        m_SpawnedEntities.push_back(spawned);
        m_PendingSpawnQueue.pop();

        return spawned;
    }

    bool Spawner::TryPlaceSafePosition(const std::shared_ptr<Entity> &entity) const {
        static constexpr int MAX_TRY_ATTEMPTS = 20;

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<float> xDist(
            m_SpawnArea.center.x - m_SpawnArea.size.x * 0.5f,
            m_SpawnArea.center.x + m_SpawnArea.size.x * 0.5f
        );
        std::uniform_real_distribution<float> yDist(
            m_SpawnArea.center.y - m_SpawnArea.size.y * 0.5f,
            m_SpawnArea.center.y + m_SpawnArea.size.y * 0.5f
        );

        for (int i = 0; i < MAX_TRY_ATTEMPTS; ++i) {
            glm::vec2 randomPos(xDist(rng), yDist(rng));
            entity->SetPosition(randomPos);

            const rect &bounds = entity->GetWorldHitBox();

            bool overlaps = false;
            for (const auto &existing: m_SpawnedEntities) {
                if (hit::intersect(bounds, existing->GetWorldHitBox())) {
                    overlaps = true;
                    break;
                }
            }
            if (!overlaps)
                return true;
        }
        return false;
    }

    void Spawner::Despawn(const std::shared_ptr<Entity> &entity) {
        if (const auto it = std::remove(m_SpawnedEntities.begin(), m_SpawnedEntities.end(), entity);
            it != m_SpawnedEntities.end()) {
            m_SpawnedEntities.erase(it, m_SpawnedEntities.end());
        }
    }

    void Spawner::Clear() {
        std::queue<std::shared_ptr<Entity>> emptyQueue;
        std::swap(m_PendingSpawnQueue, emptyQueue);
        m_SpawnedEntities.clear();
    }
} // Game
