#ifndef I_HITTABLE_H
#define I_HITTABLE_H
#include <memory>

#include "Core/Math/Shape.h"

class IHittable {
public:
    virtual ~IHittable() = default;

    [[nodiscard]] virtual const rect GetWorldHitBox() const = 0;

    [[nodiscard]] virtual bool IsOverlay(const std::shared_ptr<IHittable> &other) = 0;
};

#endif //I_HITTABLE_H
