#include "Core/Timer.h"

void Timer::Update(const float dt) {
    m_Time += dt;
}

bool Timer::Event(const int ms) {
    if (const int expectedCount = static_cast<int>(m_Time) / ms; expectedCount > m_ElapsedMap[ms]) {
        m_ElapsedMap[ms] = expectedCount;
        return true;
    }
    return false;
}

void Timer::Reset() {
    m_ElapsedMap.clear();
    m_Time = 0.0f;
}

