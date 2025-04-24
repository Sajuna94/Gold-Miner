#ifndef ORE_H
#define ORE_H
#include "Interface/IHittable.h"
#include "Interface/IMoveable.h"
#include "Util/GameObject.hpp"


class Ore : public Util::GameObject, public IHittable, public IMoveable
{
    float m_Weight;
    int m_Money;

public:
    enum class Type
    {
        ROCK,
        GOLD,
        DIAMOND,
        Count
    };

    explicit Ore(const float weight, const int money)
    {
        m_Weight = weight;
        m_Money = money;
    }

    static int RandInRange(const int min, const int max) { return rand() % (max - min + 1) + min; }

    [[nodiscard]] float GetWeight() const { return m_Weight * m_Transform.scale.x; }
    [[nodiscard]] virtual int GetMoney() const { return m_Money * m_Transform.scale.x; }

    // Interface IMoveable
    [[nodiscard]] glm::vec2 GetPosition() const final { return m_Transform.translation; }
    void SetPosition(const glm::vec2& position) final { m_Transform.translation = position; }
    void SetRotation(const float rotation) final { m_Transform.rotation = rotation; }

    // Interface IHittable
    [[nodiscard]] glm::vec2 GetHitBoxPosition() const final { return m_Transform.translation; }
    [[nodiscard]] glm::vec2 GetHitBoxSize() const override = 0;
};


#endif //ORE_H
