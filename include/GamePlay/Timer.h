#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    explicit Timer(int startSeconds, int intervalMs);

    void Update(float dt);

    bool Event();

    [[nodiscard]] int GetSecond() const;

private:
    const int m_InitialSeconds;
    const float m_Interval;
    float m_ElapsedSeconds;
    int m_LastTriggerCount = 0;
};


#endif //TIMER_H
