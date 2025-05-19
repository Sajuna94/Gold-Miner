#include "UI/Picture.h"

#include "config.hpp"

namespace UI {
    Picture::Picture(const std::string &path, const glm::vec2 position)
        : m_Image(std::make_shared<Util::Image>(path)) {
        SetDrawable(m_Image);
        m_Transform.translation = position;
    }

    void Picture::FullScreen() {
        glm::vec2 const size = m_Drawable->GetSize();
        m_Transform.scale = {WINDOW_WIDTH / size.x, WINDOW_HEIGHT / size.y};
    }
} // UI
