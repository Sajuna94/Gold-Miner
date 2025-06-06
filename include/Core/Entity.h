#ifndef ENTITY_H
#define ENTITY_H

#include "Logger.h"
#include "Interface/IHittable.h"
#include "Util/GameObject.hpp"
#include "Math/Shape.h"

class Entity : public Util::GameObject, public IHittable {
public:
    Entity() = default;

    ~Entity() override {
        Logger::Add(m_Name);
    }

    explicit Entity(std::string name) : m_Name(std::move(name)) {
    }

    [[nodiscard]] std::string &GetName() { return m_Name; }

    [[nodiscard]] rect GetHitBox() const { return m_HitBox; }

    [[nodiscard]] const rect GetWorldHitBox() const override;

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }
    virtual void SetPosition(const glm::vec2 &pos) { m_Transform.translation = pos; }
    void SetHitBox(const rect &rect) { m_HitBox = rect; }

    [[nodiscard]] const bool GetVis const 

    [[nodiscard]] bool IsOverlay(const std::shared_ptr<IHittable> &other) const override;

    virtual void Move(const glm::vec2 &delta, float dt);

protected:
    std::string m_Name;
    rect m_HitBox{};
};

#endif // ENTITY_H
