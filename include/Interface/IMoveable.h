#ifndef IMOVEABLE_H
#define IMOVEABLE_H

#include <glm/vec2.hpp>


class IMoveable
{
public:
    virtual ~IMoveable() = default;

    [[nodiscard]] virtual glm::vec2 GetPosition() const = 0;
    virtual void SetPosition(const glm::vec2& position) = 0;
    virtual void SetRotation(float rotation) = 0;
};

#endif //IMOVEABLE_H
