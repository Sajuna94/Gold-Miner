#include "Game/Spawner.h"

#include <random>


#include "Game/Factory.h"

namespace Game {
    Spawner::Spawner(const rect &area)
        : m_SpawnArea(area) {
    }

    void Spawner::SetSpawnLimits(std::unordered_map<std::string, int> limits) {
        m_SpawnLimits = std::move(limits);
    }

    std::shared_ptr<Entity> Spawner::TrySpawn() {
        if (m_Pending.empty()) {
            if (auto name = PickSpawnName()) {
                m_Pending.emplace(*name);
                --m_SpawnLimits[*name];
            } else
                return nullptr;
        }

        auto entity = Factory::CreateEntity(m_Pending.front(), 10);

        if (!entity) {
            m_Pending.pop();
            return nullptr;
        }
        if (TryPlaceSafe(entity)) {
            m_Pending.pop();
            m_Spawned.push_back(entity);
            return entity;
        }
        return nullptr;
    }

    void Spawner::Despawn(const std::shared_ptr<Entity> &entity) {
        if (const auto it = std::remove(m_Spawned.begin(), m_Spawned.end(), entity);
            it != m_Spawned.end()) {
            m_Spawned.erase(it, m_Spawned.end());
        }
    }

    void Spawner::Clear() {
        std::queue<std::string> emptyQueue;
        std::swap(m_Pending, emptyQueue);
        m_Spawned.clear();
    }

    int Spawner::GetLimitTotal() {
        int total = 0;
        for (const auto &[_, count]: m_SpawnLimits) {
            total += count;
        }
        return total;
    }

    std::optional<std::string> Spawner::PickSpawnName() {
        if (m_SpawnLimits["Rock"] > 0) {
            return "Rock";
        }

        std::vector<std::string> names;
        std::vector<int> weights;
        for (const auto &[name, limit]: m_SpawnLimits) {
            if (limit > 0) {
                names.push_back(name);
                weights.push_back(limit);
            }
        }
        if (names.empty()) return std::nullopt;
        std::discrete_distribution<size_t> dist(weights.begin(), weights.end());
        return names[dist(m_Rng)];
    }

    bool Spawner::TryPlaceSafe(const std::shared_ptr<Entity> &entity) const {
        static constexpr int MAX_TRY_ATTEMPTS = 20;

        const auto halfArea = (m_SpawnArea.size - entity->GetHitBox().size) * 0.5f;

        std::uniform_real_distribution<float> xDist(
            m_SpawnArea.center.x - halfArea.x,
            m_SpawnArea.center.x + halfArea.x
        );
        std::uniform_real_distribution<float> yDist(
            m_SpawnArea.center.y - halfArea.y,
            m_SpawnArea.center.y + halfArea.y
        );

        for (int i = 0; i < MAX_TRY_ATTEMPTS; ++i) {
            glm::vec2 randomPos(xDist(m_Rng), yDist(m_Rng));
            entity->SetPosition(randomPos);

            const rect &bounds = entity->GetWorldHitBox();

            bool overlaps = false;
            for (const auto &existing: m_Spawned) {
                if (hit::intersect(bounds, existing->GetWorldHitBox())) {
                    overlaps = true;
                    break;
                }
            }
            if (!overlaps) {
                return true;
            }
        }
        return false;
    }

    void Spawner::AddSpawned(const std::shared_ptr<Entity> &entity) {
        m_Spawned.emplace_back(entity);
    }
} // Game
