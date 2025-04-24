#ifndef MINER_H
#define MINER_H

#include "Pickaxe.h"
#include "UI/Picture.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/SFX.hpp"

class Miner final : public Util::GameObject
{
public:
    explicit Miner(glm::vec2 position);

    void Update(float dt) const;

    void Move(float dt, int direction);

    [[nodiscard]] std::shared_ptr<Pickaxe> GetPickaxe() const { return m_Pickaxe; }
    [[nodiscard]] glm::vec2 GetThrownPosition() const { return m_ThrownPosition; }

    void StopPickaxe() const;
    void ThrowPickaxe();
    void ReturnPickaxe() const;

private:
    std::shared_ptr<Pickaxe> m_Pickaxe;
    std::shared_ptr<UI::Picture> m_Rope;
    std::array<std::shared_ptr<UI::Picture>, 2> m_Wheels;

    std::shared_ptr<UI::Picture> m_RedLine;
    glm::vec2 m_ThrownPosition = {0, 0};
};


#endif //MINER_H
