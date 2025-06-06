#include "UI/TextBox.h"

namespace UI {
    TextBox::TextBox(float size, const std::string &text, const Align align, const Style style)
        : m_Align(align),
          m_Text(std::make_shared<Util::Text>(ResolveFontPath(style), size, " ")),
          m_Padding(0.0f) {
        SetDrawable(m_Text);
        SetText(text);
    }

    void TextBox::SetColor(const Util::Color color) const {
        m_Text->SetColor(color);
    }

    void TextBox::SetText(const std::string &text) {
        const float lastWidth = GetScaledSize().x;
        m_Text->SetText(text);

        float offset = 0.0f;
        switch (m_Align) {
            case Align::LEFT: offset = (GetScaledSize().x - lastWidth) * 0.5f;
                break;
            case Align::RIGHT: offset = (GetScaledSize().x - lastWidth) * -0.5f;
                break;
            default: break;
        }
        m_Transform.translation.x += offset;
        m_Padding += offset;
    }

    void TextBox::SetPosition(const glm::vec2 &pos) {
        m_Transform.translation = pos + glm::vec2(m_Padding, 0.0f);
    }

    std::string TextBox::ResolveFontPath(const Style style) {
        switch (style) {
            case Style::Sans: return SAMSUNG_FONT_PATH;
            case Style::Caveat: return CAVEAT_FONT_PATH;
            default: return SAMSUNG_FONT_PATH;
        }
    }
} // UI
