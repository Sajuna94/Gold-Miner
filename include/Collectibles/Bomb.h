#ifndef BOMB_H
#define BOMB_H

#include "Core/Entity.h"
#include "Util/Animation.hpp"
#include "Util/SFX.hpp"


class Bomb final : public Entity
{
public:
    explicit Bomb(const float zIndex)
        : Entity({{0, 0}, {55, 68}}),
          m_ExplosionSound(std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/medium-explosion.mp3")),
          m_Animation(std::make_shared<Util::Animation>(
              std::vector<std::string>{
                  RESOURCE_DIR"/Collectible/Bomb/bomb-0.png",
                  RESOURCE_DIR"/Collectible/Bomb/bomb-1.png",
                  RESOURCE_DIR"/Collectible/Bomb/bomb-2.png",
                  RESOURCE_DIR"/Collectible/Bomb/bomb-3.png",
                  RESOURCE_DIR"/Collectible/Bomb/bomb-4.png",
                  RESOURCE_DIR"/Collectible/Bomb/bomb-5.png",
                  RESOURCE_DIR"/Collectible/Bomb/bomb-6.png",
                  RESOURCE_DIR"/Collectible/Bomb/bomb-7.png",
              },
              false, 50, false, 100))
    {
        SetDrawable(m_Animation);
        SetZIndex(zIndex);
    }

    // 我が名はめぐみん。紅魔族随一の魔法の使い手にして、爆裂魔法を操りし者。我が力、見るがいい！エクスプロージョン！
    void Explosion()
    {
        m_ExplosionSound->Play();
        m_Animation->Play();
        m_Animation->SetCurrentFrame(1);
        m_ZIndex = 100;
        m_Transform.scale = {2.5, 2.5};
        m_Radius = 52.5f * m_Transform.scale.x;
    }

    [[nodiscard]] bool IsBlownUp() const
    {
        return m_Animation->GetState() == Util::Animation::State::ENDED;
    }

    [[nodiscard]] bool InTheBlowRange(const std::shared_ptr<ICollidable>& collidable) const
    {
        return m_Radius >= length(GetPosition() - collidable->m_Transform.translation);
    }

private:
    std::shared_ptr<Util::SFX> m_ExplosionSound;
    std::shared_ptr<Util::Animation> m_Animation;
    float m_Radius = 0.0f;
};

#endif //BOMB_H
