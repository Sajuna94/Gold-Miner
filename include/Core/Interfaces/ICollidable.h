#ifndef ICOLLIDABLE_H
#define ICOLLIDABLE_H
#include <memory>
#include <glm/vec2.hpp>

struct HitBox
{
    glm::vec2 offset;
    glm::vec2 size;
};

class ICollidable
{
public:
    virtual ~ICollidable() = default;

    [[nodiscard]] virtual glm::vec2 GetWorldPosition() const = 0;
    [[nodiscard]] virtual HitBox GetHitBox() const = 0;

    [[nodiscard]] bool IsOverlay(const std::shared_ptr<ICollidable>& other) const
    {
        const glm::vec2 center1 = GetWorldPosition() + GetHitBox().offset;
        const glm::vec2 halfSize1 = GetHitBox().size * 0.5f;

        const glm::vec2 center2 = other->GetWorldPosition() + other->GetHitBox().offset;
        const glm::vec2 halfSize2 = other->GetHitBox().size * 0.5f;

        return
            std::abs(center1.x - center2.x) < (halfSize1.x + halfSize2.x) &&
            std::abs(center1.y - center2.y) < (halfSize1.y + halfSize2.y);
    }
};

#endif //ICOLLIDABLE_H
