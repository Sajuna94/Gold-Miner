#ifndef ROCK_H
#define ROCK_H
#include "Core/Entity.h"
#include "Core/Interfaces/IGrabbable.h"

class Rock final : public Entity, public IGrabbable
{
public:
    explicit Rock(const float zIndex)
        : IGrabbable(50, 10),
          m_Image(std::make_shared<Util::Image>(
              std::vector<std::string>{
                  RESOURCE_DIR"/Collectible/Rock/rock-1.png",
                  RESOURCE_DIR"/Collectible/Rock/rock-2.png",
              }[RandInRange(0, 1)]))

    {
        SetDrawable(m_Image);
        SetZIndex(zIndex);

        const float multiplier = RandInRange(60, 150) / 100.0f;
        m_HitBox = {{0, 0}, GetScaledSize() * 0.9f * multiplier};
        m_Transform.scale *= multiplier;
        m_Weight *= log(1 + multiplier);
        m_Money *= multiplier;
    }

private:
    std::shared_ptr<Util::Image> m_Image;
};

#endif //ROCK_H
