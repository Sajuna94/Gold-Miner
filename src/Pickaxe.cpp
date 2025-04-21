#include "Pickaxe.h"
#include <cmath>

#include "config.hpp"
#define PI 3.141592653589793;

void Pickaxe::SetDragOre(const std::shared_ptr<Ore>& ore)
{
    m_DragOre = ore;
    m_DragOre->SetZIndex(m_ZIndex - 1);
    m_MoveSpeed /= (ore->GetWeight() * 0.1f);
    const glm::vec2 dPos = {
        sin(m_Transform.rotation) * (10 + ore->GetHitBox().size.y * 0.5f),
        -cos(m_Transform.rotation) * (10 + ore->GetHitBox().size.y * 0.5f),
    };
    m_DragOre->SetRotation(m_Transform.rotation);
    m_DragOre->SetPosition(m_Transform.translation + dPos);
}

std::shared_ptr<Ore> Pickaxe::TakeDragOre()
{
    m_MoveSpeed = 300.0f;
    auto temp = m_DragOre;
    m_DragOre = nullptr;
    return temp;
}

void Pickaxe::UpdateNextMove(const float dt)
{
    const glm::vec2 curPos = m_Transform.translation;
    const glm::vec2 dPos = {
        sin(m_Transform.rotation) * m_MoveSpeed * dt,
        -cos(m_Transform.rotation) * m_MoveSpeed * dt
    };

    if (m_CurrentState == State::THROWN)
        m_Transform.translation = curPos + dPos;
    else if (m_CurrentState == State::RETURN)
    {
        m_Transform.translation = curPos - dPos;
        if (m_DragOre)
            m_DragOre->SetPosition(m_DragOre->GetPosition() - dPos);
    }
}

void Pickaxe::UpdateAngle(const float dt)
{
    angle += direction * rotateSpeed;

    if (angle < -85.0f) direction = 1.0f;
    if (85.0f < angle) direction = -1.0f;

    m_Transform.rotation = angle * dt;
}
