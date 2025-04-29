#ifndef DIAMOND_H
#define DIAMOND_H
#include "Core/Entity.h"
#include "Core/Interfaces/IGrabbable.h"
#include "Util/Animation.hpp"

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
              true, 400, true, 100))
    {
        SetDrawable(m_Animation);
        m_Animation->SetCurrentFrame(RandInRange(0, static_cast<int>(m_Animation->GetFrameCount()) - 1));
        SetZIndex(zIndex);
    }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};


#endif //DIAMOND_H
