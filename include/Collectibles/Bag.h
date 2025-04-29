#ifndef BAG_H
#define BAG_H
#include "Core/Entity.h"
#include "Core/Interfaces/IGrabbable.h"
#include "Util/Image.hpp"

class Bag final : public Entity, public IGrabbable
{
public:
    explicit Bag(const float zIndex)
        : Entity({{0, 0}, {60, 70}}),
          IGrabbable(20, RandInRange(100, 200)),
          m_Image(std::make_shared<Util::Image>(RESOURCE_DIR"/Collectible/bag.png"))
    {
        SetDrawable(m_Image);
        SetZIndex(zIndex);
    }

private:
    std::shared_ptr<Util::Image> m_Image;
};


#endif //BAG_H
