//
// Created by ianli on 2025/4/14.
//

#ifndef GOLD_H
#define GOLD_H
#include "Ore.h"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"


class Gold final : public Ore
{
public:
    explicit Gold(const int small = 60, const int mid = 20):
        Ore(20, 200),
        m_Animation(std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR"/Ore/Gold/gold-0.png",
                RESOURCE_DIR"/Ore/Gold/gold-1.png",
                RESOURCE_DIR"/Ore/Gold/gold-2.png",
                RESOURCE_DIR"/Ore/Gold/gold-3.png",
                RESOURCE_DIR"/Ore/Gold/gold-4.png",
            },
            true, 300, true, 300))
    {
        SetDrawable(m_Animation);

        if (const int size = RandInRange(1, 100); size <= small)
            m_Transform.scale *= RandInRange(20, 50) / 100.0f;
        else if (size <= small + mid)
            m_Transform.scale *= RandInRange(70, 100) / 100.0f;
        else
            m_Transform.scale *= RandInRange(120, 150) / 100.0f;
    }

    [[nodiscard]] glm::vec2 GetHitBoxSize() const override { return glm::vec2({93, 93}) * m_Transform.scale.x; }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif //GOLD_H
