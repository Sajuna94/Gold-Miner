#ifndef PICKAXE_H
#define PICKAXE_H
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Interface/IHittable.h"
#include "Interface/IMoveable.h"
#include "Ore.h"

class Pickaxe final : public Util::GameObject, public IHittable, public IMoveable
{
public:
    enum class State { STOP, THROWN, RETURN };

private:
    enum class Direction { LEFT, RIGHT };

    State m_CurrentState = State::STOP;
    std::shared_ptr<Ore> m_DragOre;

public:
    explicit Pickaxe(const glm::vec2& position, const float zindex = 50)
        : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Pickaxe/pickaxe.png"), zindex)
    {
        SetPivot({0, 6});
        m_Transform.translation = position;
    }

    void Stop() { m_CurrentState = State::STOP; }
    void Throw() { m_CurrentState = State::THROWN; }
    void Return() { m_CurrentState = State::RETURN; }

    [[nodiscard]] State GetState() const { return m_CurrentState; }
    [[nodiscard]] float GetRotation() const { return m_Transform.rotation; }

    // Ore
    void SetDragOre(const std::shared_ptr<Ore>& ore);
    std::shared_ptr<Ore> TakeDragOre();

    // Update
    void UpdateAngle(float dt);
    void UpdateNextMove(float dt);

    // Interface IMoveable
    [[nodiscard]] glm::vec2 GetPosition() const override { return m_Transform.translation; }
    void SetPosition(const glm::vec2& position) override { m_Transform.translation = position; }
    void SetRotation(const float rotation) override { m_Transform.rotation = rotation; }

    // Interface IHittable
    glm::vec2 GetHitBoxPosition() const override { return m_Transform.translation; }
    glm::vec2 GetHitBoxSize() const override { return {30, 15}; }

private:
    float m_MoveSpeed = 300.0f, m_RotateSpeed = 100.0f;
    Direction m_Direction = Direction::LEFT;


    float angle = 0.0f, direction = 1.0f;
    float moveSpeed = 300.0f;
};


#endif //PICKAXE_H
