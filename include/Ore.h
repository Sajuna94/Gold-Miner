#ifndef ORE_H
#define ORE_H
#include "IHittable.h"
#include "Util/GameObject.hpp"


class Ore : public Util::GameObject, public IHittable
{
private:
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

    void SetRotation(const float rotation) { m_Transform.rotation = rotation; }
    [[nodiscard]] glm::vec2 GetPosition() const { return m_Transform.translation; }
    void SetPosition(const glm::vec2 position) { m_Transform.translation = position; }
    glm::vec2 GetCenterPoint() const override { return m_Transform.translation; }
    [[nodiscard]] float GetWeight() const { return m_Weight; }
    [[nodiscard]] int GetMoney() const { return m_Money; }
};


#endif //ORE_H
