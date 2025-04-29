#include "GamePlay/EntitySpawner.h"

#include "config.hpp"
#include "Collectibles/Diamond.h"
#include "Collectibles/Gold.h"
#include "Collectibles/Rock.h"
#include "Collectibles/Bag.h"
#include "Collectibles/Bomb.h"

#define MAX_SPAWN_ATTEMPTS 5

namespace
{
    using EntityFactory = std::function<std::shared_ptr<Entity>()>;

    const std::vector<EntityFactory> kCollectibleFactories = {
        []() { return std::make_shared<Diamond>(10); },
        []() { return std::make_shared<Gold>(10); },
        []() { return std::make_shared<Rock>(10); },
        []() { return std::make_shared<Bag>(10); },
        []() { return std::make_shared<Bomb>(10); }
    };
}

bool EntitySpawner::TrySpawnEntity()
{
    if (m_EntitySpawnQueue.empty())
        return false;

    const auto& entity = m_EntitySpawnQueue.front();

    const int width = static_cast<int>(WINDOW_WIDTH - entity->GetHitBox().size.x) / 2;
    const int height = static_cast<int>(WINDOW_HEIGHT - entity->GetHitBox().size.y) / 2;

    // Random place entity
    int tryPlaceCount = 0;
    while (tryPlaceCount < MAX_SPAWN_ATTEMPTS)
    {
        entity->SetPosition({
            RandInRange(-width, width),
            RandInRange(-height, height - 200),
        });

        if (std::none_of(m_SpawnedEntities.begin(), m_SpawnedEntities.end(),
                         [&](const auto& other) { return other->IsOverlay(entity); }))
        {
            break;
        }
        tryPlaceCount += 1;
    }

    // If place safe
    if (tryPlaceCount < MAX_SPAWN_ATTEMPTS)
    {
        m_SpawnedEntities.insert(entity);
        m_EntitiesBuffer.push_back(entity);
        m_EntitySpawnQueue.pop();
        return true;
    }
    return false;
}

void EntitySpawner::QueueRandomCollectible(const std::shared_ptr<Entity>& entity)
{
    m_EntitySpawnQueue.push(entity ? entity : GenerateRandomCollectible());
}

std::shared_ptr<Entity> EntitySpawner::GenerateRandomCollectible()
{
    int randIndex = RandInRange(0, static_cast<int>(kCollectibleFactories.size()) - 1);
    if (RandInRange(0, 10) > 2)
        randIndex = 4;
    return kCollectibleFactories[randIndex]();
}

std::vector<std::shared_ptr<Util::GameObject>> EntitySpawner::ExtractEntities()
{
    return std::exchange(m_EntitiesBuffer, {});
}
