#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    explicit Timer(int startTime, bool countDown = false);

    void Update(float dt);

    bool Event();

    [[nodiscard]] int GetTimer() const;

private:
    const int m_InitialTime;
    bool m_CountDown;
    float m_Time;
    int m_LastSecond;
};


#endif //TIMER_H
