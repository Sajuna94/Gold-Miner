#include "Game/Factory.h"

#include "Core/Math/Random.h"
#include "Util/Animation.hpp"

namespace Game {
    std::shared_ptr<Entity> Factory::CreateRandomEntity(const float zIndex) {
        static std::array<std::function<std::shared_ptr<Entity>(float)>, 4> creators = {
            CreateDiamond,
            CreateGold,
            CreateStone,
            CreateBomb,
        };
        return creators[rand_int(0, creators.size() - 1)](zIndex);
    }

    std::shared_ptr<Collection> Factory::CreateDiamond(const float zIndex) {
        auto anim = std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-1.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-2.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-3.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-4.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-5.png",
                RESOURCE_DIR "/Textures/Entity/Collection/diamond-6.png",
            },
            true, rand_int(150, 200), true, 50
        );
        anim->SetCurrentFrame(rand_int(0, static_cast<int>(anim->GetFrameCount()) - 1));

        auto diamond = std::make_unique<Collection>(std::move(anim), "Diamond", 500, 150.0f);
        diamond->SetHitBox(rect({30, 20}));
        diamond->SetZIndex(zIndex);

        return diamond;
    }

    std::shared_ptr<Collection> Factory::CreateGold(const float zIndex) {
        auto anim = std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR "/Textures/Entity/Collection/gold-1.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-2.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-3.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-4.png",
                RESOURCE_DIR "/Textures/Entity/Collection/gold-5.png",
            },
            true, rand_int(350, 500), true, 50
        );
        anim->SetCurrentFrame(rand_int(0, static_cast<int>(anim->GetFrameCount()) - 1));

        auto gold = std::make_unique<Collection>(std::move(anim), "Gold", 500, 70.0f);
        gold->SetHitBox(rect({88, 88}));
        gold->SetZIndex(zIndex);

        return gold;
    }

    std::shared_ptr<Collection> Factory::CreateStone(const float zIndex) {
        static constexpr std::array<const char *, 2> paths = {
            RESOURCE_DIR "/Textures/Entity/Collection/stone-1.png",
            RESOURCE_DIR "/Textures/Entity/Collection/stone-2.png"
        };
        auto image = std::make_shared<Util::Image>(paths[rand_int(0, 1)]);

        auto stone = std::make_unique<Collection>(std::move(image), "Stone", 50, 300.0f);
        stone->SetHitBox(rect(stone->GetScaledSize() * 0.9f));
        stone->SetZIndex(zIndex);

        return stone;
    }

    std::shared_ptr<Bomb> Factory::CreateBomb(float zIndex) {
        auto static sound = std::make_shared<Util::SFX>(RESOURCE_DIR "/Sounds/medium-explosion.mp3");

        auto bomb = std::make_unique<Bomb>(zIndex);
        bomb->SetHitBox(rect({55, 68}));
        bomb->SetSound(sound);

        return bomb;
    }
} // Game
