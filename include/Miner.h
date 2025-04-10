#ifndef MINER_H
#define MINER_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Miner final : public Util::GameObject {
public:
    Miner() : GameObject(
        std::make_unique<Util::Image>(RESOURCE_DIR"/res/iphonehd/miner.png"), 10) {
        m_Transform.translation = {0.0F, 120.0F};
        m_Transform.scale = {0.7F, 0.7F};
    }
};


#endif //MINER_H
