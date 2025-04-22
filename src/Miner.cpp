#include "Miner.h"
#include "Util/Input.hpp"

Miner::Miner(const glm::vec2 position): GameObject(
    std::make_unique<Util::Image>(RESOURCE_DIR"/Character/miner.png"), 2)
{
    m_Transform.translation = position;
    m_Transform.scale = {0.68F, 0.68F};

    m_Pickaxe = std::make_shared<Pickaxe>(position + glm::vec2(-5.5, -26));

    m_Rope = std::make_shared<UI::Picture>(
        RESOURCE_DIR"/Color/black.png",
        position + m_Pickaxe->GetPosition()
    );
    m_Rope->SetZIndex(m_Rope->GetZIndex() + 1);

    m_Wheels[0] = std::make_shared<UI::Picture>(
        RESOURCE_DIR"/Character/wheel.png",
        position + glm::vec2(-43, -77)
    );
    m_Wheels[0]->SetScaleSize({0.8f, 0.8f});
    m_Wheels[1] = std::make_shared<UI::Picture>(
        RESOURCE_DIR"/Character/wheel.png",
        position + glm::vec2(41, -77)
    );
    m_Wheels[1]->SetScaleSize({0.8f, 0.8f});

    std::vector<std::shared_ptr<GameObject>> children = {m_Pickaxe, m_Rope, m_Wheels[0], m_Wheels[1]};
    for (const auto& child : children)
        AddChild(child);
}

void Miner::Update(const float dt) const
{
    switch (m_Pickaxe->GetState())
    {
    case Pickaxe::State::STOP:
        if (!Util::Input::IsKeyPressed(Util::Keycode::SPACE))
            m_Pickaxe->UpdateAngle(dt);
        break;
    default:
        m_Pickaxe->UpdateNextMove(dt);
        m_Rope->SetPosition((m_ThrownPosition + m_Pickaxe->GetPosition()) * 0.5f);
        m_Rope->SetScaleSize({3, glm::length(m_ThrownPosition - m_Pickaxe->GetPosition())});
    }
}

void Miner::StopPickaxe() const
{
    m_Pickaxe->SetPosition(m_ThrownPosition);
    m_Pickaxe->Stop();
}

void Miner::ThrowPickaxe()
{
    m_ThrownPosition = m_Pickaxe->GetPosition();
    m_Rope->SetRotation(m_Pickaxe->GetRotation());
    m_Pickaxe->Throw();
}

void Miner::ReturnPickaxe() const
{
    m_Pickaxe->Return();
}

void Miner::Move(const float dt, const int direction)
{
    const float mover = static_cast<float>(direction) * 100.0f * dt;
    m_Transform.translation.x += mover;
    for (const auto& child : GetChildren())
    {
        auto const temp = std::dynamic_pointer_cast<IMoveable>(child);
        temp->SetPosition(temp->GetPosition() + glm::vec2(mover, 0.0f));
    }
    for (const auto& wheel : m_Wheels)
        wheel->SetRotation(wheel->GetTransform().rotation + 10.0f * dt * -direction);
}
