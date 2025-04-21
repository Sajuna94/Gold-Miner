#ifndef PICKAXE_H
#define PICKAXE_H
#include "IHittable.h"
#include "IMoveable.h"
#include "Ore.h"
#include "UI/Picture.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Pickaxe final : public Util::GameObject, public IHittable, public IMoveable
{
public:
    enum class State
    {
        STOP,
        THROWN,
        RETURN,
    };

private:
    State m_CurrentState = State::STOP;
    std::shared_ptr<Ore> m_DragOre;
    float m_MoveSpeed = 300.0f;

    // std::shared_ptr<UI::Picture> m_Rope;
public:
    explicit Pickaxe(const glm::vec2& position, const float zindex = 50)
        : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Pickaxe/pickaxe.png"), zindex)
    {
        SetPivot({0, 6});
        SetHitBox({0, 0}, {30, 15});
        m_Transform.translation = position;
    }

    void Stop() { m_CurrentState = State::STOP; }
    void Throw() { m_CurrentState = State::THROWN; }
    void Return() { m_CurrentState = State::RETURN; }

    [[nodiscard]] State GetState() const { return m_CurrentState; }
    [[nodiscard]] float GetRotation() const { return m_Transform.rotation; }

    [[nodiscard]] glm::vec2 GetPosition() const override { return m_Transform.translation; }
    void SetPosition(const glm::vec2& position) override { m_Transform.translation = position; }
    [[nodiscard]] glm::vec2 GetCenterPoint() const override { return m_Transform.translation; }

    void SetDragOre(const std::shared_ptr<Ore>& ore);
    std::shared_ptr<Ore> TakeDragOre();
    void UpdateAngle(float dt);
    void UpdateNextMove(float dt);

private:
    float angle = 0.0f, rotateSpeed = 1.8f, direction = 1.0f;
    float moveSpeed = 300.0f;
};


#endif //PICKAXE_H
