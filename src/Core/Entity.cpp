#include "Core/Entity.h"

void Entity::Move(const glm::vec2 &delta, const float dt) {
    m_Transform.translation += delta * dt;
}

const rect Entity::GetWorldHitBox() const {
    return rect(m_HitBox.center + m_Transform.translation, m_HitBox.size);
}

bool Entity::IsOverlay(const std::shared_ptr<IHittable> &other) const {
    return hit::intersect(GetWorldHitBox(), other->GetWorldHitBox());
}
