#include "Game/Factory.h"

#include "Core/Math/Random.h"
#include "Util/Animation.hpp"

namespace Game {
    std::shared_ptr<Entity> Factory::CreateEntity(const std::string &name, const float zIndex) {
        if (const auto it = Registry().find(name); it != Registry().end()) {
            return it->second(zIndex);
        }
        return nullptr;
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

        const int persent = rand_int(1, 10);
        float mult;
        if (persent <= 4)
            mult = rand_int(50, 80) / 100.0f;
        else if (persent <= 9)
            mult = rand_int(120, 150) / 100.0f;
        else
            mult = rand_int(170, 200) / 100.0f;

        gold->m_Transform.scale = glm::vec2(mult);
        gold->SetMoney(gold->GetMoney() * mult);
        gold->SetWeight(gold->GetWeight() * mult);
        gold->SetHitBox(rect(gold->GetHitBox().size * mult));

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

        const int persent = rand_int(1, 10);
        float mult;
        if (persent <= 8)
            mult = rand_int(70, 100) / 100.0f;
        else
            mult = rand_int(150, 170) / 100.0f;

        stone->m_Transform.scale = glm::vec2(mult);
        stone->SetMoney(stone->GetMoney() * mult);
        stone->SetWeight(stone->GetWeight() * mult);
        stone->SetHitBox(rect(stone->GetHitBox().size * mult));

        return stone;
    }

    // TODO:
    std::shared_ptr<Collection> Factory::CreateRock(float zIndex) {
        static constexpr std::array<const char *, 2> paths = {
            // RESOURCE_DIR "/Textures/Entity/Collection/stone-1.png",
            RESOURCE_DIR "/Textures/Entity/Collection/stone-2.png"
        };
        auto image = std::make_shared<Util::Image>(paths[rand_int(0, 1)]);
    }

    std::shared_ptr<Bomb> Factory::CreateBomb(float zIndex, float radius) {
        auto static s_Anim = std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR "/Textures/Effect/explosion-1.png",
                RESOURCE_DIR "/Textures/Effect/explosion-2.png",
                RESOURCE_DIR "/Textures/Effect/explosion-3.png",
                RESOURCE_DIR "/Textures/Effect/explosion-4.png",
                RESOURCE_DIR "/Textures/Effect/explosion-5.png",
                RESOURCE_DIR "/Textures/Effect/explosion-6.png",
                RESOURCE_DIR "/Textures/Effect/explosion-7.png",
            },
            false, 50, false, 50
        );
        auto static s_Sound = std::make_shared<Util::SFX>(RESOURCE_DIR "/Sounds/medium-explosion.mp3");

        auto bomb = std::make_unique<Bomb>(zIndex, radius);
        bomb->SetHitBox(rect({55, 68}));
        bomb->SetEffect(s_Anim);
        bomb->SetSound(s_Sound);

        return bomb;
    }

    std::shared_ptr<Entity> Factory::CreateTnt(const float zIndex) {
        auto static s_Img = std::make_shared<Util::Image>(RESOURCE_DIR "/Textures/tnt.png");

        auto tnt = std::make_shared<Entity>("Tnt");
        tnt->SetDrawable(s_Img);
        tnt->SetZIndex(zIndex);
        tnt->m_Transform.scale = glm::vec2(0.5f);

        return tnt;
    }


    void Factory::Recycle(const std::shared_ptr<Entity>& entity) {
        s_Pool[entity->GetName()].emplace(entity);
    }

} // Game
