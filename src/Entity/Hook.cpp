#include "Entity/Hook.h"

Hook::Hook(const float zIndex): Entity("Hook") {
    m_Drawable = std::make_unique<Util::Image>(RESOURCE_DIR "/Textures/Entity/hook.png");
    m_HitBox = rect({0, 0}, {15, 8});
    m_Pivot = {0, 6};
    SetZIndex(zIndex);

    m_Rope = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Entity/rope.png");
    m_Rope->SetZIndex(zIndex - 0.1f);
    AddChild(m_Rope);
}

void Hook::Stop() {
    m_State = State::STOPPED;

    SetPosition(m_ThrownPosition);
    m_Rope->SetVisible(false);
}

void Hook::Throw() {
    m_State = State::THROWN;

    m_ThrownPosition = GetPosition();
    m_VelocityDirection = {
        sin(m_Transform.rotation) * kMoveSpeed,
        -cos(m_Transform.rotation) * kMoveSpeed
    };
    m_Rope->SetVisible(true);
    m_Rope->m_Transform.translation = GetPosition();
    m_Rope->m_Transform.rotation = m_Transform.rotation;
}

void Hook::Return() {
    m_State = State::RETURN;
    m_VelocityDirection *= -1.0f;
}

bool Hook::HasReturned() const {
    return GetPosition().y >= m_ThrownPosition.y;
}

void Hook::HookCollection(const std::shared_ptr<Collection> &collection) {
    m_HookedCollection = collection;

    collection->m_Transform.rotation = m_Transform.rotation;
    collection->SetZIndex(m_ZIndex - 0.1f);
    collection->SetPosition(GetPosition() + glm::vec2(
                                sin(m_Transform.rotation),
                                -cos(m_Transform.rotation)
                            ) * (collection->GetHitBox().size.y * 0.5f + 10.0f));
    m_VelocityDirection /= (collection->GetWeight() / 100.0f) * 0.5f;
}

std::shared_ptr<Collection> Hook::GetHookedCollection() const {
    return m_HookedCollection.lock();
}

void Hook::ReleaseCollection() {
    m_HookedCollection.reset();
}

void Hook::Advance(const float dt) {
    // Move the hook
    Move(m_VelocityDirection, dt);

    // Update the rope
    m_Rope->m_Transform.translation = (GetPosition() + m_ThrownPosition) * 0.5f;
    m_Rope->m_Transform.scale = {3, length(GetPosition() - m_ThrownPosition)};

    // Update the hooked collection
    if (const auto hooked = GetHookedCollection())
        hooked->Move(m_VelocityDirection, dt);
}

void Hook::Swing(const float dt) {
    m_TimeAcc += dt;
    m_SwingAngle = kMaxSwingAngle * sin(kSwingSpeed * m_TimeAcc);
    m_Transform.rotation = glm::radians(m_SwingAngle);
}
