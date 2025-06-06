#include "UI/Picture.h"

#include "config.hpp"

namespace UI {
    Picture::Picture(const std::string &path, const glm::vec2 position)
        : m_Image(std::make_shared<Util::Image>(path)) {
        SetDrawable(m_Image);
        m_Transform.translation = position;
    }

    void Picture::FullScreen(const glm::vec2 &view) {
        glm::vec2 const size = m_Drawable->GetSize();
        m_Transform.scale = {view.x / size.x, view.y / size.y};
    }

    void Picture::AlignTo(const Align &align, const glm::vec2 &offset) {
        glm::vec2 const half = (glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) - GetScaledSize()) * 0.5f;
        switch (align) {
            case Align::TOP:
                m_Transform.translation.y = half.y;
                break;
            case Align::RIGHT:
                m_Transform.translation.x = half.x;
                break;
            case Align::BOTTOM:
                m_Transform.translation.y = -half.y;
                break;
            case Align::LEFT:
                m_Transform.translation.x = -half.x;
                break;
            case Align::TOP_LEFT:
                m_Transform.translation = glm::vec2(-half.x, half.y);
                break;
            case Align::TOP_RIGHT:
                m_Transform.translation = half;
        }
        m_Transform.translation += offset;
    }
} // UI
