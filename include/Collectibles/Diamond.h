#ifndef DIAMOND_H
#define DIAMOND_H
#include "Core/Entity.h"
#include "Core/Interfaces/IGrabbable.h"

class Diamond final : public Entity, public IGrabbable
{
public:
    explicit Diamond(const float zIndex)
        : Entity({{0, 0}, {31, 21}}),
          IGrabbable(5, 500),
          m_Animation(std::make_shared<Util::Animation>(
              std::vector<std::string>{
                  RESOURCE_DIR"/Collectible/Diamond/diamond-1.png",
                  RESOURCE_DIR"/Collectible/Diamond/diamond-2.png",
                  RESOURCE_DIR"/Collectible/Diamond/diamond-3.png",
                  RESOURCE_DIR"/Collectible/Diamond/diamond-4.png",
                  RESOURCE_DIR"/Collectible/Diamond/diamond-5.png",
                  RESOURCE_DIR"/Collectible/Diamond/diamond-6.png",
              },
              true, 100, true, 100))
    {
        SetDrawable(m_Animation);
        SetZIndex(zIndex);
    }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};


#endif //DIAMOND_H
