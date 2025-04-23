#ifndef BOMB_H
#define BOMB_H
#include "Interface/IHittable.h"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Bomb final : public Util::GameObject, public IHittable, public IMoveable
{
public:
    explicit Bomb():
        m_Animation(std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR"/Bomb/bomb-0.png",
                RESOURCE_DIR"/Bomb/bomb-1.png",
                RESOURCE_DIR"/Bomb/bomb-2.png",
                RESOURCE_DIR"/Bomb/bomb-3.png",
                RESOURCE_DIR"/Bomb/bomb-4.png",
                RESOURCE_DIR"/Bomb/bomb-5.png",
                RESOURCE_DIR"/Bomb/bomb-6.png",
                RESOURCE_DIR"/Bomb/bomb-7.png",
            },
            false, 50, false, 100))
    {
        SetDrawable(m_Animation);
    }

    bool IsExplosionFinished() const
    {
        return  m_Animation->GetState() == Util::Animation::State::ENDED;
    }

    bool IsInExplosionRange(const std::shared_ptr<IHittable>& hittable) const
    {
        const float radius = 52.5f * m_Transform.scale.x;
        const glm::vec2 centerPt = GetHitBoxPosition();

        return radius > length(centerPt - hittable->GetHitBoxPosition());
    }

    void Explosion()
    {
        m_Animation->Play();
        m_Animation->SetCurrentFrame(1);
        m_ZIndex = 100;
        m_Transform.scale = {2.5, 2.5};
    }

    // Interface IMoveable
    [[nodiscard]] glm::vec2 GetPosition() const override { return m_Transform.translation; }
    void SetPosition(const glm::vec2& position) override { m_Transform.translation = position; }
    void SetRotation(const float rotation) override { m_Transform.rotation = rotation; }

    // Interface IHittable
    [[nodiscard]] glm::vec2 GetHitBoxPosition() const override { return m_Transform.translation; }
    [[nodiscard]] glm::vec2 GetHitBoxSize() const override { return {55, 68}; }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif //BOMB_H
