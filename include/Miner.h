#ifndef MINER_H
#define MINER_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Miner final : public Util::GameObject
{
public:
    explicit Miner(const glm::vec2 position) : GameObject(
        std::make_unique<Util::Image>(RESOURCE_DIR"/Character/miner.png"), 2)
    {
        m_Transform.translation = position;
        m_Transform.scale = {0.68F, 0.68F};
    }
};


#endif //MINER_H
