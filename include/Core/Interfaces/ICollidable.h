#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H

#include "Util/GameObject.hpp"

struct HitBox
{
    glm::vec2 offset;
    glm::vec2 size;
};

class ICollidable : virtual public Util::GameObject
{
protected:
    HitBox m_HitBox{};

public:
    ~ICollidable() override = default;

    /**
     * @brief Get the object's HitBox.
     * @return The HitBox (offset and size).
     */
    [[nodiscard]] virtual HitBox GetHitBox() { return m_HitBox; }

    /**
     * @brief Check if this object overlaps with another.
     * @return True if they overlap, false otherwise.
     */
    [[nodiscard]] bool IsOverlay(const std::shared_ptr<ICollidable>& other) const
    {
        const glm::vec2 center1 = m_Transform.translation + m_HitBox.offset;
        const glm::vec2 halfSize1 = m_HitBox.size * 0.5f;

        const glm::vec2 center2 = other->GetTransform().translation + other->GetHitBox().offset;
        const glm::vec2 halfSize2 = other->GetHitBox().size * 0.5f;

        return
            std::abs(center1.x - center2.x) < (halfSize1.x + halfSize2.x) &&
            std::abs(center1.y - center2.y) < (halfSize1.y + halfSize2.y);
    }
};

#endif //ICOLLIDABLE_H
