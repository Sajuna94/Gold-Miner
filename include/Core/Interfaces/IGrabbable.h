#ifndef IGRABBABLE_H
#define IGRABBABLE_H

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

    void SetWeight(const float weight) { m_Weight = weight; }
};

#endif //IGRABBABLE_H
