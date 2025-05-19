#include "Game/Factory.h"
#include "Core/Math/Random.h"

namespace Game {
    std::shared_ptr<Collection> Factory::CreateDiamond() {
        auto anim = std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-1.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-2.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-3.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-4.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-5.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-6.png",
            },
            true, 50, true, 50
        );
        auto diamond = std::make_unique<Collection>(std::move(anim), "Diamond", 500, 150.0f);
        diamond->SetHitBox(rect({20, 30}));
        return diamond;
    }

    std::shared_ptr<Collection> Factory::CreateGold() {
        auto anim = std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR "/Textures/Entity/Collection/gold-1.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-2.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-3.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-4.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-5.png",
            },
            true, 50, true, 50
        );
        auto gold = std::make_unique<Collection>(std::move(anim), "Gold", 500, 70.0f);
        gold->SetHitBox(rect({35, 25}));
        return gold;
    }

    std::shared_ptr<Collection> Factory::CreateStone() {
        static constexpr std::array<const char *, 2> paths = {
            RESOURCE_DIR "/Textures/Entity/Collection/stone-1.png",
            RESOURCE_DIR "/Textures/Entity/Collection/stone-2.png"
        };
        auto image = std::make_shared<Util::Image>(paths[rand_int(0, 1)]);
        auto stone = std::make_unique<Collection>(std::move(image), "Stone", 50, 300.0f);
        stone->SetHitBox(rect(stone->GetScaledSize() * 0.8f));
        return stone;
    }
} // Game
