#ifndef IHITTABLE_H
#define IHITTABLE_H
#include <glm/vec2.hpp>

class IHittable
{
public:
    virtual ~IHittable() = default;

    [[nodiscard]] virtual glm::vec2 GetHitBoxPosition() const = 0;
    [[nodiscard]] virtual glm::vec2 GetHitBoxSize() const = 0;

    [[nodiscard]] bool IsOverlay(const IHittable& other) const
    {
        const glm::vec2 center1 = GetHitBoxPosition();
        const glm::vec2 halfSize1 = GetHitBoxSize() * 0.5f;

        const glm::vec2 center2 = other.GetHitBoxPosition();
        const glm::vec2 halfSize2 = other.GetHitBoxSize() * 0.5f;

        return
            std::abs(center1.x - center2.x) < halfSize1.x + halfSize2.x &&
            std::abs(center1.y - center2.y) < halfSize1.y + halfSize2.y;
    }
};


#endif //IHITTABLE_H
