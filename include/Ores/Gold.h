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
    explicit Gold():
        Ore(20, 20),
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
        m_Transform.translation = {0, 0};
        m_ZIndex = 32;
        SetDrawable(m_Animation);
        SetHitBox({0, 0}, {93, 93});
    }

private:
    std::shared_ptr<Util::Animation> m_Animation;
};

#endif //GOLD_H
