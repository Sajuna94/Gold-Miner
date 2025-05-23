#ifndef COLLECTION_H
#define COLLECTION_H
#include "Core/Entity.h"


class Collection final : public Entity {
public:
    Collection(const std::shared_ptr<Core::Drawable> &drawable, std::string name, int money, float weight);

    // Getter
    [[nodiscard]] int GetMoney() const { return m_Money; }
    [[nodiscard]] float GetWeight() const { return m_Weight; }

    // Setter
    void SetMoney(int money);
    void SetWeight(float weight);

private:
    int m_Money;
    float m_Weight;
};


#endif //COLLECTION_H
