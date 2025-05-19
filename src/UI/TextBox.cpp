#include "UI/TextBox.h"

namespace UI {
    TextBox::TextBox(float size, const std::string &text, const Align align, const std::string &path)
        : m_Text(std::make_shared<Util::Text>(path, size, text)),
          m_Align(align) {
        SetDrawable(m_Text);
    }

    void TextBox::SetColor(const Util::Color color) const {
        m_Text->SetColor(color);
    }

    void TextBox::SetText(const std::string &text) {
        const float tempWidth = GetScaledSize().x;
        m_Text->SetText(text);

        auto offset = glm::vec2(0.0f, 0.0f);
        if (m_Align == Align::LEFT) {
            offset.x = -(GetScaledSize().x - tempWidth) * 0.5f;
        } else if (m_Align == Align::RIGHT) {
            offset.x = (GetScaledSize().x - tempWidth) * 0.5f;
        }
        m_Transform.translation += offset;
    }
} // UI
