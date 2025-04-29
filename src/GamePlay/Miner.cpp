#include "GamePlay/Miner.h"

#include <utility>

Miner::Miner(const float zIndex, const float pickaxeZIndex)
    : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Miner/miner.png"), zIndex)
{
    m_Transform.translation = {5.5, 255};
    m_Transform.scale = {0.68F, 0.68F};

    m_Pickaxe = std::make_shared<Entity>(RESOURCE_DIR"/Miner/pickaxe.png", pickaxeZIndex);
    m_Pickaxe->SetPosition(m_Transform.translation + glm::vec2(-5.5, -26));
    m_Pickaxe->SetPivot({0, 6});
    m_Pickaxe->SetHitBox({{0, 0}, {30, 15}});

    m_Rope = std::make_shared<UI::Picture>(RESOURCE_DIR"/Miner/rope.png", zIndex + 2);
    m_Rope->SetPosition(m_Transform.translation + m_Pickaxe->GetPosition());

    m_Wheels[0] = std::make_shared<UI::Picture>(RESOURCE_DIR"/Miner/wheel.png", zIndex + 1);
    m_Wheels[0]->SetPosition(m_Transform.translation + glm::vec2(-43, -77));
    m_Wheels[0]->SetScaleSize({0.8f, 0.8f});
    m_Wheels[1] = std::make_shared<UI::Picture>(RESOURCE_DIR"/Miner/wheel.png", zIndex + 1);
    m_Wheels[1]->SetPosition(m_Transform.translation + glm::vec2(41, -77));
    m_Wheels[1]->SetScaleSize({0.8f, 0.8f});

    m_ThrownPosition = m_Pickaxe->GetPosition();

    std::vector<std::shared_ptr<GameObject>> children = {m_Pickaxe, m_Rope, m_Wheels[0], m_Wheels[1]};
    for (const auto& child : children)
        AddChild(child);
}

void Miner::Update(const float dt)
{
    if (m_State == State::STOPPED)
    {
        m_PickaxeRotateAngle += m_PickaxeRotateDirection * m_PickaxeRotateSpeed * dt;

        if (m_PickaxeRotateAngle < -85.0f)
        {
            m_PickaxeRotateAngle = -85.0f;
            m_PickaxeRotateDirection = -m_PickaxeRotateDirection;
        }
        else if (m_PickaxeRotateAngle > 85.0f)
        {
            m_PickaxeRotateAngle = 85.0f;
            m_PickaxeRotateDirection = -m_PickaxeRotateDirection;
        }

        m_Pickaxe->m_Transform.rotation = glm::radians(m_PickaxeRotateAngle);
    }
    else
    {
        m_Pickaxe->Move(m_DeltaMovePosition, dt);
        m_Rope->SetPosition((m_ThrownPosition + m_Pickaxe->GetPosition()) * 0.5f);
        m_Rope->SetScaleSize({3, length(m_ThrownPosition - m_Pickaxe->GetPosition())});

        if (m_GrabItem)
        {
            const auto& entity = std::dynamic_pointer_cast<Entity>(m_GrabItem);
            entity->Move(m_DeltaMovePosition, dt);
        }
    }
}

void Miner::StopPickaxe()
{
    m_State = State::STOPPED;
    m_Pickaxe->SetPosition(m_ThrownPosition);
}

void Miner::ThrowPickaxe()
{
    m_State = State::THROWING;
    m_ThrownPosition = m_Pickaxe->GetPosition();
    m_Rope->SetRotation(m_Pickaxe->GetTransform().rotation);

    m_DeltaMovePosition = {
        sin(m_Pickaxe->GetTransform().rotation) * m_PickaxeMoveSpeed,
        -cos(m_Pickaxe->GetTransform().rotation) * m_PickaxeMoveSpeed
    };
}

void Miner::ReturnPickaxe()
{
    m_State = State::RETURN;
    m_DeltaMovePosition = -m_DeltaMovePosition;

    // when grabbing item
    if (const auto& grabItem = std::dynamic_pointer_cast<IGrabbable>(m_GrabItem))
        m_DeltaMovePosition /= grabItem->GetWeight() * 0.1f;
}

std::shared_ptr<Entity> Miner::GetGrabItem()
{
    return std::exchange(m_GrabItem, nullptr);
}

void Miner::SetGrabItem(const std::shared_ptr<IGrabbable>& grabItem)
{
    m_GrabItem = std::dynamic_pointer_cast<Entity>(grabItem);
    m_GrabItem->SetZIndex(m_Pickaxe->GetZIndex() - 1);
    m_GrabItem->m_Transform.rotation = m_Pickaxe->GetTransform().rotation;
    m_GrabItem->SetPosition(m_Pickaxe->GetPosition() + glm::vec2(
        sin(m_Pickaxe->GetTransform().rotation),
        -cos(m_Pickaxe->GetTransform().rotation)
    ) * (10 + m_GrabItem->GetHitBox().size.y * 0.5f));
}


void Miner::Move(const glm::vec2& delta, const float dt)
{
    const glm::vec2 mover = delta * m_MoveSpeed;
    const float direction = delta.x < 0 ? 1 : -1;

    Entity::Move(mover, dt);
    for (const auto& child : GetChildren())
    {
        const auto& moveable = std::dynamic_pointer_cast<IMoveable>(child);
        moveable->Move(mover, dt);
    }
    for (const auto& wheel : m_Wheels)
        wheel->SetRotation(wheel->GetTransform().rotation + direction * m_WheelRotateSpeed * dt);
}

bool Miner::IsReturnBack() const
{
    return m_Pickaxe->GetPosition().y > m_ThrownPosition.y;
}
