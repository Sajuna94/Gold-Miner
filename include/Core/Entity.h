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

class Entity : public Util::GameObject, public ICollidable, public IMoveable
{
protected:
    HitBox m_HitBox{};

public:
    ~Entity() override = default;

    explicit Entity() = default;

    explicit Entity(const HitBox& hitBox) : m_HitBox(hitBox)
    {
    }

    explicit Entity(const std::string& imagePath, const float zIndex): GameObject(
        std::make_unique<Util::Image>(imagePath), zIndex)
    {
    }

    void SetHitBox(const HitBox& hitBox) { m_HitBox = hitBox; }

    // Interface IMoveable
    [[nodiscard]] glm::vec2 GetPosition() const final { return m_Transform.translation; }
    void SetPosition(const glm::vec2& position) final { m_Transform.translation = position; }
    void SetRotation(const float rotation) override { m_Transform.rotation = rotation; }

    // Interface ICollidable
    [[nodiscard]] glm::vec2 GetWorldPosition() const final { return m_Transform.translation; }
    [[nodiscard]] HitBox GetHitBox() const final { return m_HitBox; }
};


#endif //ENTITY_H
