#ifndef MINER_H
#define MINER_H

#include "Character.h"
#include "Pickaxe.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Miner final : public Util::GameObject
{
public:
    explicit Miner(glm::vec2 position);

    void Update(float dt);

    void Move(float dt, int direction);
    std::shared_ptr<Pickaxe> m_Pickaxe;
    std::shared_ptr<UI::Picture> m_Rope;
    std::shared_ptr<UI::Picture> m_RedLine;
private:
    glm::vec2 m_ThrownPosition;
    std::array<std::shared_ptr<UI::Picture>, 2> m_Wheels;
};


#endif //MINER_H
