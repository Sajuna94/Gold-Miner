#include "GamePlay/Timer.h"

Timer::Timer(const int startTime, const bool countDown)
    : m_InitialTime(startTime),
      m_CountDown(countDown),
      m_Time(static_cast<float>(startTime)),
      m_LastSecond(GetTimer())
{
}

void Timer::Update(const float dt)
{
    if (m_CountDown)
    {
        m_Time -= dt;
        if (m_Time <= 0)
            m_Time = 0;
    }
    else
        m_Time += dt;
}

bool Timer::Event()
{
    if (const int currentSecond = GetTimer(); currentSecond != m_LastSecond)
    {
        m_LastSecond = currentSecond;
        return true;
    }
    return false;
}

int Timer::GetTimer() const
{
    return static_cast<int>(m_Time);
}
