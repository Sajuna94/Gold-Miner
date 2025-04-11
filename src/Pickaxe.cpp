#include "Pickaxe.h"
#include <cmath>
#include <iostream>

#include "config.hpp"
#include "Util/Time.hpp"
#define PI 3.141592653589793;


void Pickaxe::Throw()
{
    if (currentThrowState != ThrowState::STOP)
        return;
    printf("[~] Pickaxe start thrown\n");
    currentThrowState = ThrowState::THROWN;
}

void Pickaxe::Update()
{
    const float dt = Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (currentThrowState == ThrowState::STOP)
        UpdateAngle(dt);
    else
    {
        const glm::vec2 curPos = m_Transform.translation;

        if (IsOutOfBounds(curPos))
        {
            currentThrowState = ThrowState::RETURN;
            printf("[^] Pickaxe out of range (%.2f, %.2f)\n", curPos.x, curPos.y);
        }
        if (curPos.y > defaultPosition.y)
        {
            currentThrowState = ThrowState::STOP;
            m_Transform.translation = defaultPosition;
        }

        const glm::vec2 dPos = {
            sin(m_Transform.rotation) * moveSpeed * dt,
            cos(m_Transform.rotation) * -moveSpeed * dt
        };

        if (currentThrowState == ThrowState::THROWN)
            m_Transform.translation = curPos + dPos;
        if (currentThrowState == ThrowState::RETURN)
            m_Transform.translation = curPos - dPos;
    }
}

bool Pickaxe::IsOutOfBounds(const glm::vec2 pos) const
{
    const glm::vec2 size = GetScaledSize();
    return
        pos.y < -((WINDOW_HEIGHT - size.y) / 2.0f) ||
        pos.x < -((WINDOW_WIDTH - size.x) / 2.0f) ||
        pos.x > (WINDOW_WIDTH - size.x) / 2.0f;
}


void Pickaxe::UpdateAngle(const float dt)
{
    angle += direction * rotateSpeed;

    if (angle < -85.0f) direction = 1.0f;
    if (85.0f < angle) direction = -1.0f;

    m_Transform.rotation = angle * dt;
}
