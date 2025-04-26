#ifndef IGRABBABLE_H
#define IGRABBABLE_H

#include <random>

class IGrabbable
{
protected:
    float m_Weight{};
    int m_Money{};

public:
    virtual ~IGrabbable() = default;

    IGrabbable(const float weight, const int money) :
        m_Weight(weight), m_Money(money)
    {
    }

    virtual float GetWeight() { return m_Weight; }
    virtual int GetMoney() { return m_Money; }

    static int RandInRange(const int left, const int right)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution dis(left, right);
        return dis(gen);
    }
};

#endif //IGRABBABLE_H
