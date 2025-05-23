#include "Entity/Collection.h"

Collection::Collection(const std::shared_ptr<Core::Drawable> &drawable,
                       std::string name, const int money, const float weight)
    : Entity(std::move(name)), m_Money(money), m_Weight(weight) {
    SetDrawable(drawable);
}

void Collection::SetMoney(const int money) {
    if (money < 0)
        throw std::invalid_argument("money cannot be negative");
    m_Money = money;
}

void Collection::SetWeight(const float weight) {
    if (weight < 1.0f)
        throw std::invalid_argument("weight cannot be less than 1");
    m_Weight = weight;
}
