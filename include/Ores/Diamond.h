#ifndef DIAMOND_H
#define DIAMOND_H
#include "Ore.h"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Diamond final : public Ore {
public:
    Diamond()
        : m_Animation(std::make_shared<Util::Animation>(
            std::vector<std::string>{
                RESOURCE_DIR"/res/iphonehd/level-sheet/diamond-1.png",
                RESOURCE_DIR"/res/iphonehd/level-sheet/diamond-2.png",
                RESOURCE_DIR"/res/iphonehd/level-sheet/diamond-3.png",
                RESOURCE_DIR"/res/iphonehd/level-sheet/diamond-4.png",
                RESOURCE_DIR"/res/iphonehd/level-sheet/diamond-5.png",
                RESOURCE_DIR"/res/iphonehd/level-sheet/diamond-6.png",
            },
            true, 100, true, 100)) {
        m_Transform.translation = {0, 0};
        m_ZIndex = 20;
        SetDrawable(m_Animation);
        // m_Animation->GetCurrentFrameIndex()
    }

    void Update();

private:
    std::shared_ptr<Util::Animation> m_Animation;
};


#endif //DIAMOND_H
