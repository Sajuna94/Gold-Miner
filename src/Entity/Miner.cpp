#include "Entity/Miner.h"

Miner::Miner(const float zIndex) : Entity("Miner") {
    m_Drawable = std::make_unique<Util::Image>(RESOURCE_DIR "/Textures/Entity/miner.png");
    m_Transform.scale = glm::vec2(0.68f);
    SetZIndex(zIndex);

    m_Hook = std::make_shared<Hook>(zIndex + 50);
    AddChild(m_Hook);

    m_Wheels[0] = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Entity/wheel.png");
    m_Wheels[0]->m_Transform.scale = glm::vec2(0.8f);
    m_Wheels[0]->SetZIndex(zIndex + 1);
    AddChild(m_Wheels[0]);
    m_Wheels[1] = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Entity/wheel.png");
    m_Wheels[1]->m_Transform.scale = glm::vec2(0.8f);
    m_Wheels[1]->SetZIndex(zIndex + 1);
    AddChild(m_Wheels[1]);

    SetPosition(m_Transform.translation);
}

bool Miner::IsMinerStopped(float epsilon) const {
    return std::abs(m_Velocity) < epsilon;
}

void Miner::SmoothMove(const int dir, const float dt) {
    if (abs(GetPosition().x) > 350)
        m_Velocity *= -1.0f;
    else if (IsMinerStopped()) {
        m_Velocity = static_cast<float>(dir) * kInitSpeed;
    } else {
        m_Velocity = glm::clamp((m_Velocity + static_cast<float>(dir) * kAccelRate * dt) * kDecelFactor,
                                -kMaxSpeed, kMaxSpeed);
    }

    const float mover = m_Velocity * dt;
    m_Transform.translation.x += mover;
    for (const auto &child: GetChildren()) {
        child->m_Transform.translation.x += mover;
    }
    for (const auto &wheel: m_Wheels) {
        wheel->m_Transform.rotation -= glm::radians(mover) * 2.5f;
    }
}

void Miner::SetPosition(const glm::vec2 &pos) {
    m_Transform.translation = pos;
    m_Hook->SetPosition(GetPosition() + glm::vec2(-6, -26.5));
    m_Wheels[0]->m_Transform.translation = GetPosition() + glm::vec2(-42, -80);
    m_Wheels[1]->m_Transform.translation = GetPosition() + glm::vec2(42, -80);
}
