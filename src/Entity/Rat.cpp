#include "Entity/Rat.h"

#include "config.hpp"
#include "Core/Math/Random.h"
#include "Util/Animation.hpp"

Rat::Rat()
    : Collection(
          std::make_shared<Util::Animation>(
              std::vector<std::string>{
                  RESOURCE_DIR "/Textures/Entity/Collection/gem-mouse-6.png",
                  RESOURCE_DIR "/Textures/Entity/Collection/gem-mouse-7.png",
              },
              false, 50, true, 50
          ), "Rat", 1, 100.0f),
      m_NextMovementMs(static_cast<float>(GetRandomTick())), m_Boundary((WINDOW_WIDTH - GetScaledSize().x) * 0.5f) {
    SetDir(rand_int(0, 1) * 2 - 1);
}

void Rat::Update(const float dt) {
    if (m_NextMovementMs <= 0) {
        m_NextMovementMs = static_cast<float>(GetRandomTick());
        m_IsMoving = !m_IsMoving;
        if (m_IsMoving)
            SetDir(rand_int(0, 1) * 2 - 1);
        HandleMovementAnmi();
    }
    m_NextMovementMs -= dt;

    if (m_IsMoving) {
        Move({0.17f * static_cast<float>(m_CurrentDir), 0}, dt);
        if (abs(GetPosition().x) > m_Boundary) {
            SetDir(-m_CurrentDir);
            m_Transform.translation.x = glm::clamp(GetPosition().x, -m_Boundary, m_Boundary);
        }
    }
}

int Rat::GetRandomTick() const {
    if (m_IsMoving)
        return rand_int(2500, 4000);
    return rand_int(300, 800);
}

void Rat::SetDir(const int dir) {
    if (dir == 1) {
        m_Transform.scale.x = 1;
        m_CurrentDir = dir;
    } else {
        m_Transform.scale.x = -1;
        m_CurrentDir = dir;
    }
}

void Rat::HandleMovementAnmi() const {
    const auto anmi = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    if (m_IsMoving) {
        anmi->Play();
    } else {
        anmi->Pause();
    }
}
