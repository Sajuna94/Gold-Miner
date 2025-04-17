#ifndef IHITTABLE_H
#define IHITTABLE_H
#include <glm/vec2.hpp>
#include "Util/GameObject.hpp"


struct HitBox
{
    glm::vec2 offset;
    glm::vec2 size;
};

class IHittable
{
private:
    HitBox m_HitBox = {};

public:
    virtual ~IHittable() = default;

    virtual glm::vec2 GetCenterPoint() const = 0;
    [[nodiscard]] HitBox GetHitBox() const { return m_HitBox; }
    void SetHitBox(const glm::vec2 offset, const glm::vec2 size) { m_HitBox = {offset, size}; }

    bool IsOverlappingWith(const IHittable& other) const
    {
        const HitBox a = {GetCenterPoint() + m_HitBox.offset, m_HitBox.size / 2.0f};
        const HitBox b = {other.GetCenterPoint() + other.GetHitBox().offset, other.GetHitBox().size / 2.0f};

        glm::vec2 aMin = a.offset - a.size * 0.5f;
        glm::vec2 aMax = a.offset + a.size * 0.5f;
        glm::vec2 bMin = b.offset - b.size * 0.5f;
        glm::vec2 bMax = b.offset + b.size * 0.5f;

        return (aMin.x < bMax.x && aMax.x > bMin.x &&
                aMin.y < bMax.y && aMax.y > bMin.y);
    }
};


#endif //IHITTABLE_H
