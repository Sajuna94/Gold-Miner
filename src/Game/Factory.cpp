#include "Game/Factory.h"

#include "Core/Math/Random.h"
#include "Util/Animation.hpp"

namespace Game {
    std::shared_ptr<Entity> Factory::CreateEntity(const std::string &name, const float zIndex) {
        if (const auto it = FactoryCatalog().find(name); it != FactoryCatalog().end()) {
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

        auto diamond = std::make_unique<Collection>(std::move(anim), "Diamond", 500, 70.0f);
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

        auto gold = std::make_unique<Collection>(std::move(anim), "Gold", 200, 150.0f);
        gold->SetHitBox(rect({88, 88}));
        gold->SetZIndex(zIndex);

        const int persent = rand_int(1, 10);
        float mult;
        if (persent <= 2)
            mult = rand_int(50, 80) / 100.0f;
        else if (persent <= 9)
            mult = rand_int(100, 120) / 100.0f;
        else
            mult = rand_int(150, 170) / 100.0f;

        gold->m_Transform.scale = glm::vec2(mult);
        gold->SetMoney(gold->GetMoney() * log1p(mult));
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

        auto stone = std::make_unique<Collection>(std::move(image), "Stone", 50, 350.0f);
        stone->SetHitBox(rect(stone->GetScaledSize() * 0.9f));
        stone->SetZIndex(zIndex);

        const int persent = rand_int(1, 10);
        float mult;
        if (persent <= 8)
            mult = rand_int(70, 100) / 100.0f;
        else
            mult = rand_int(150, 170) / 100.0f;

        stone->m_Transform.scale = glm::vec2(mult);
        stone->SetWeight(stone->GetWeight() * log1p(mult));
        stone->SetHitBox(rect(stone->GetHitBox().size * mult));

        return stone;
    }

    std::shared_ptr<Entity> Factory::CreateRock(const float zIndex) {
        const auto static image = std::make_shared<Util::Image>(RESOURCE_DIR "/Textures/Entity/rock-layer.png");

        auto rock = std::make_shared<Entity>("Rock");
        rock->SetDrawable(image);
        rock->SetZIndex(zIndex);

        const auto mult = glm::vec2(static_cast<float>(rand_int(80, 150)) / 100.0f * 0.8f, 0.4f);
        rock->m_Transform.scale = mult;
        rock->SetHitBox(rect(glm::vec2(253, 207) * mult));

        return rock;
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
        tnt->m_Transform.scale = glm::vec2(0.4f);

        return tnt;
    }

    std::shared_ptr<Collection> Factory::CreateBag(const float zIndex) {
        auto static s_Img = std::make_shared<Util::Image>(RESOURCE_DIR "/Textures/Entity/Collection/bag.png");

        auto bag = std::make_shared<Collection>(s_Img, "Bag", rand_int(300, 500), 200.0f);
        bag->SetHitBox(rect({68, 74}));
        bag->SetDrawable(s_Img);
        bag->SetZIndex(zIndex);

        return bag;
    }

    std::shared_ptr<Rat> Factory::CreateRat(const float zIndex) {
        auto rat = std::make_shared<Rat>();
        rat->SetZIndex(zIndex);
        rat->SetHitBox(rect({53, 42}));

        return rat;
    }

    std::shared_ptr<Collection> Factory::CreatePulledGold(const float zIndex) {
        auto anim = std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR "/Textures/Entity/Collection/pulled-gold-2.png",
                RESOURCE_DIR "/Textures/Entity/Collection/pulled-gold-3.png",
                RESOURCE_DIR "/Textures/Entity/Collection/pulled-gold-4.png",
                RESOURCE_DIR "/Textures/Entity/Collection/pulled-gold-5.png",
                RESOURCE_DIR "/Textures/Entity/Collection/pulled-gold-6.png",
                RESOURCE_DIR "/Textures/Entity/Collection/pulled-gold-7.png",
                RESOURCE_DIR "/Textures/Entity/Collection/pulled-gold-1.png",
            },
            true, 70, true, rand_int(500, 750)
        );
        anim->SetCurrentFrame(rand_int(0, static_cast<int>(anim->GetFrameCount()) - 1));

        auto gold = std::make_unique<Collection>(std::move(anim), "PulledGold", 400, 150.0f);
        gold->SetHitBox(rect({85, 91}));
        gold->SetZIndex(zIndex);

        return gold;
    }
} // Game
