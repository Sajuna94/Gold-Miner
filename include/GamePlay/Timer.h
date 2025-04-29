#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    /**
     * @brief Construct a timer.
     * @param startSeconds Initial time in seconds.
     * @param interval Interval between events in milliseconds.
     */
    explicit Timer(int startSeconds, int interval);

    /**
     * @brief Advance the timer by a delta time.
     * @param dt time passed in seconds.
     */
    void Update(float dt);

    /**
     * @brief Check if the timer has reached a new interval.
     * @return True if a new interval was reached, false otherwise.
     */
    bool Event();

    /**
     * @return The current second of the timer
     */
    [[nodiscard]] int GetSecond() const;

private:
    const int m_InitialSeconds;
    const float m_Interval;
    float m_ElapsedSeconds;
    int m_LastTriggerCount = 0;
};


#endif //TIMER_H
