#ifndef ROCK_H
#define ROCK_H
#include "Ore.h"
#include "Util/Animation.hpp"

class Rock final : public Ore
{
public:
    explicit Rock():
        Ore(50, 5),
        m_Animation(std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR"/Ore/Rock/rock-1.png",
                RESOURCE_DIR"/Ore/Rock/rock-2.png",
            },
            false, 100, false, 100))
    {
        SetDrawable(m_Animation);
        m_ZIndex = 31;
    }

    [[nodiscard]] glm::vec2 GetHitBoxSize() const override { return {60, 60}; }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif //ROCK_H
