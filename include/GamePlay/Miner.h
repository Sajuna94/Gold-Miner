#ifndef MINER_H
#define MINER_H
#include "Core/Entity.h"
#include "Core/Interfaces/IGrabbable.h"
#include "UI/Picture.h"

class Miner final : public Entity
{
public:
    enum class State
    {
        STOPPED,
        THROWING,
        RETURN,
    };

    explicit Miner(float zIndex, float pickaxeZIndex);

private:
    // Miner State
    State m_State = State::STOPPED;

    // Drawable Object
    std::shared_ptr<Entity> m_Pickaxe;
    std::shared_ptr<UI::Picture> m_Rope;
    std::array<std::shared_ptr<UI::Picture>, 2> m_Wheels;

    // Interact Object
    std::shared_ptr<Entity> m_GrabItem = nullptr;

    // Miner variable
    const float m_MoveSpeed = 100.0f;
    const float m_WheelRotateSpeed = 10.0f;

    // Pickaxe variable
    glm::vec2 m_ThrownPosition{};
    glm::vec2 m_DeltaMovePosition{};
    const float m_PickaxeMoveSpeed = 300.0f;
    const float m_PickaxeRotateSpeed = 100.0f;
    float m_PickaxeRotateDirection = -1.0f;
    float m_PickaxeRotateAngle = 0.0f;

public:
    void Update(float dt);
    void Move(const glm::vec2& delta, float dt) override;
    [[nodiscard]] bool IsReturnBack() const;

    // Miner State Control
    void StopPickaxe();
    void ThrowPickaxe();
    void ReturnPickaxe();

    // Getter
    [[nodiscard]] State GetState() const { return m_State; }
    [[nodiscard]] std::shared_ptr<Entity> GetPickaxe() const { return m_Pickaxe; }
    std::shared_ptr<Entity> GetGrabItem();

    // Setter
    void SetGrabItem(const std::shared_ptr<IGrabbable>& grabItem);
};

#endif //MINER_H
