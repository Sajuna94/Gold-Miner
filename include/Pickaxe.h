#ifndef PICKAXE_H
#define PICKAXE_H
#include "IHittable.h"
#include "Ore.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Pickaxe final : public Util::GameObject, public IHittable
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

public:
    explicit Pickaxe(const glm::vec2& position, const float zindex = 50)
        : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Pickaxe/pickaxe.png"), zindex)
    {
        m_Transform.translation = position;
    }

    void Stop() { m_CurrentState = State::STOP; }
    void Throw() { m_CurrentState = State::THROWN; }
    void Return() { m_CurrentState = State::RETURN; }

    [[nodiscard]] State GetState() const { return m_CurrentState; }
    [[nodiscard]] float GetRotation() const { return m_Transform.rotation; }

    [[nodiscard]] glm::vec2 GetPosition() const { return m_Transform.translation; }
    void SetPosition(const glm::vec2 position) { m_Transform.translation = position; }
    glm::vec2 GetCenterPoint() const override { return m_Transform.translation; }

    void SetDragOre(const std::shared_ptr<Ore>& ore);
    std::shared_ptr<Ore> TakeDragOre();
    void Update(float dt);
    void UpdateAngle(float dt);
    void UpdateMove(float dt);

private:
    float angle = 0.0f, rotateSpeed = 1.8f, direction = 1.0f;
    float moveSpeed = 300.0f;

};


#endif //PICKAXE_H
