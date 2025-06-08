#include "Entity/Bomb.h"

Bomb::Bomb(const float zIndex, const float radius)
    : Entity("Bomb"), m_Radius(radius),
      m_Effect(std::make_shared<Util::Animation>(
          std::vector<std::string>{
              RESOURCE_DIR "/Textures/Effect/explosion-1.png",
              RESOURCE_DIR "/Textures/Effect/explosion-2.png",
              RESOURCE_DIR "/Textures/Effect/explosion-3.png",
              RESOURCE_DIR "/Textures/Effect/explosion-4.png",
              RESOURCE_DIR "/Textures/Effect/explosion-5.png",
              RESOURCE_DIR "/Textures/Effect/explosion-6.png",
              RESOURCE_DIR "/Textures/Effect/explosion-7.png",
          },
          false, 50, false, 50
      )) {
    SetDrawable(std::make_unique<Util::Image>(RESOURCE_DIR "/Textures/Entity/bomb.png"));
    SetZIndex(zIndex);
}

void Bomb::Explode() {
    SetZIndex(90);
    SetDrawable(m_Effect);
    m_Effect->Play();
    if (m_Sound) m_Sound->Play();

    m_Transform.scale = glm::vec2(m_Radius * 2 / 100.0f);
}

bool Bomb::HasExploded() const {
    return m_Effect->GetState() == Util::Animation::State::ENDED;
}

bool Bomb::InBlastRadius(const std::shared_ptr<Entity> &entity) const {
    return m_Radius >= length(GetPosition() - entity->GetPosition());
}

void Bomb::SetEffect(const std::shared_ptr<Util::Animation> &effect) {
    m_Effect = effect;
}

void Bomb::SetSound(const std::shared_ptr<Util::SFX> &sound) {
    m_Sound = sound;
}
