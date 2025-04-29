#ifndef GOLD_H
#define GOLD_H
#include "Core/Entity.h"
#include "Core/Interfaces/IGrabbable.h"

class Gold final : public Entity, public IGrabbable
{
public:
    explicit Gold(const float zIndex)
        : Entity({{0, 0}, {90, 90}}),
          IGrabbable(20, 200),
          m_Animation(std::make_shared<Util::Animation>(
              std::vector<std::string>{
                  RESOURCE_DIR"/Collectible/Gold/gold-0.png",
                  RESOURCE_DIR"/Collectible/Gold/gold-1.png",
                  RESOURCE_DIR"/Collectible/Gold/gold-2.png",
                  RESOURCE_DIR"/Collectible/Gold/gold-3.png",
                  RESOURCE_DIR"/Collectible/Gold/gold-4.png",
              },
              true, 300, true, 300))
    {
        SetDrawable(m_Animation);
        m_Animation->SetCurrentFrame(RandInRange(0, static_cast<int>(m_Animation->GetFrameCount()) - 1));
        SetZIndex(zIndex);

        const float multiplier = GetMultiplier();
        m_HitBox.size *= multiplier;
        m_Transform.scale *= multiplier;
        m_Weight *= log(1 + multiplier);
        m_Money = multiplier * m_Money;
    }

private:
    std::shared_ptr<Util::Animation> m_Animation;

    static float GetMultiplier()
    {
        const int randomValue = RandInRange(1, 100);
        if (randomValue <= 60)
            return RandInRange(20, 50) / 100.0f;
        if (randomValue <= 90)
            return RandInRange(70, 100) / 100.0f;
        return RandInRange(120, 150) / 100.0f;
    }
};

#endif //GOLD_H
