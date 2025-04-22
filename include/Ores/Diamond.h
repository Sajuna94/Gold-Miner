#ifndef DIAMOND_H
#define DIAMOND_H
#include "Ore.h"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Diamond final : public Ore
{
public:
    explicit Diamond():
        Ore(5, 100),
        m_Animation(std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR"/Ore/Diamond/diamond-1.png",
                RESOURCE_DIR"/Ore/Diamond/diamond-2.png",
                RESOURCE_DIR"/Ore/Diamond/diamond-3.png",
                RESOURCE_DIR"/Ore/Diamond/diamond-4.png",
                RESOURCE_DIR"/Ore/Diamond/diamond-5.png",
                RESOURCE_DIR"/Ore/Diamond/diamond-6.png",
            },
            true, 100, true, 100))
    {
        SetDrawable(m_Animation);
        m_ZIndex = 33;
    }

    [[nodiscard]] glm::vec2 GetHitBoxSize() const override { return {31, 21}; }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};


#endif //DIAMOND_H
