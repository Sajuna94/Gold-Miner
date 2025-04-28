#include "GamePlay/Timer.h"

Timer::Timer(const int startSeconds, const int intervalMs)
    : m_InitialSeconds(startSeconds),
      m_Interval(static_cast<float>(intervalMs) / 1000.0f),
      m_ElapsedSeconds(static_cast<float>(startSeconds))
{
}

void Timer::Update(const float dt)
{
    m_ElapsedSeconds += dt;
}

bool Timer::Event()
{
    if (static_cast<int>(m_ElapsedSeconds / m_Interval) > m_LastTriggerCount)
    {
        m_LastTriggerCount += 1;
        return true;
    }
    return false;
}

int Timer::GetSecond() const
{
    return static_cast<int>(m_ElapsedSeconds);
}
