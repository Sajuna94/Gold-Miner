#ifndef ENTITY_H
#define ENTITY_H

#include <random>

#include "Interfaces/ICollidable.h"
#include "Interfaces/IMoveable.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

[[maybe_unused]] static int RandInRange(const int left, const int right)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(left, right);
    return dis(gen);
}

class Entity : virtual public Util::GameObject, public ICollidable, public IMoveable
{
public:
    ~Entity() override = default;

    explicit Entity() = default;

    explicit Entity(const HitBox& hitBox)
    {
        m_HitBox = hitBox;
        m_Transform.translation = {0, 0};
    }

    explicit Entity(const std::string& imagePath, const float zIndex): GameObject(
        std::make_unique<Util::Image>(imagePath), zIndex)
    {
    }

    void SetHitBox(const HitBox& hitBox) { m_HitBox = hitBox; }

private:
    std::shared_ptr<Util::Image> m_Image;
};


#endif //ENTITY_H
