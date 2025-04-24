#ifndef ROCK_H
#define ROCK_H
#include "Ore.h"
#include "Util/Animation.hpp"

class Rock final : public Ore
{
public:
    explicit Rock():
        Ore(50, 10),
        m_Animation(std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR"/Ore/Rock/rock-1.png",
                RESOURCE_DIR"/Ore/Rock/rock-2.png",
            },
            false, 100, false, 100))
    {
        SetDrawable(m_Animation);
        m_Transform.scale *= RandInRange(60, 150) / 100.0f;
        m_ZIndex = 31;
    }

    [[nodiscard]] glm::vec2 GetHitBoxSize() const override { return glm::vec2({60, 60}) * m_Transform.scale.x; }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif //ROCK_H
