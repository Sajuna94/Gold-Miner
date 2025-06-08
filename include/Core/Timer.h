#ifndef TIMER_H
#define TIMER_H
#include <unordered_map>


class Timer {
public:
    explicit Timer(): m_Time(0) {
    }

    void Update(float dt);

    [[nodiscard]] bool Event(int ms);

    [[nodiscard]] int GetCount(const int ms) { return  m_ElapsedMap[ms]; }

    void Reset();
private:
    float m_Time;
    std::unordered_map<int, int> m_ElapsedMap;
};

#endif //TIMER_H
