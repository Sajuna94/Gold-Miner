#ifndef IMOVEABLE_H
#define IMOVEABLE_H

#include "Util/GameObject.hpp"

class IMoveable : virtual public Util::GameObject
{
public:
    ~IMoveable() override = default;

    [[nodiscard]] virtual glm::vec2 GetPosition() const { return m_Transform.translation; }
    virtual void SetPosition(const glm::vec2& position) { m_Transform.translation = position; }

    virtual void Move(const glm::vec2& delta, const float dt)
    {
        m_Transform.translation += delta * dt;
    }
};

#endif //IMOVEABLE_H
