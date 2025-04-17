#ifndef CHARACTER_H
#define CHARACTER_H
#include "Util/GameObject.hpp"

class Character : public Util::GameObject
{
public:
    [[nodiscard]] glm::vec2 GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2 position) { m_Transform.translation = position; }
    void SetRotation(const float rotation) { m_Transform.rotation = rotation; }
};

#endif //CHARACTER_H
