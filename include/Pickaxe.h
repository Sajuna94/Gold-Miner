#ifndef PICKAXE_H
#define PICKAXE_H
#include "IMoveable.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Pickaxe final : public Util::GameObject
{
public:
    explicit Pickaxe()
        : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/pickaxe_src/pickaxe_1_52x35.png"), 15)
    {
        m_Transform.translation = defaultPosition;
        SetPivot({0, 8});
    }

    void Throw();

    void Update();

private:
    enum class ThrowState
    {
        STOP,
        THROWN,
        RETURN,
    };

    float angle = 0.0f, rotateSpeed = 1.8f, direction = 1.0f;
    float moveSpeed = 300.0f;
    ThrowState currentThrowState = ThrowState::STOP;
    const glm::vec2 defaultPosition = {0, 200};

    void UpdateAngle(float dt);
    bool IsOutOfBounds(glm::vec2 pos) const;
};


#endif //PICKAXE_H
