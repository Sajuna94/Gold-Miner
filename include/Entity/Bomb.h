#ifndef BOMB_H
#define BOMB_H
#include "Core/Entity.h"
#include "Util/Animation.hpp"
#include "Util/SFX.hpp"


class Bomb final : public Entity {
public:
    explicit Bomb(float zIndex, float radius = 125);

    void Explode();

    [[nodiscard]] bool HasExploded() const;

    [[nodiscard]] bool InBlastRadius(const std::shared_ptr<Entity>& entity) const;

    void SetSound(const std::shared_ptr<Util::SFX>& sound);
private:
    float m_Radius;
    std::shared_ptr<Util::Animation> m_Effect;
    std::shared_ptr<Util::SFX> m_Sound;
};


#endif //BOMB_H
