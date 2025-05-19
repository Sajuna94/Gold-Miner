#include "UI/Button.h"

#include "Util/Input.hpp"

namespace UI {
    Button::Button(const std::string &imagePath)
        : m_Image(std::make_shared<Util::Image>(imagePath)),
          m_Bounds(rect(m_Image->GetSize())) {
        SetDrawable(m_Image);
    }

    bool Button::OnHover() const {
        return m_Bounds.contains(Util::Input::GetCursorPosition());
    }

    bool Button::OnClick() const {
        return Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && OnHover();
    }

    void Button::SetImage(const std::string &imagePath) const {
        m_Image->SetImage(imagePath);
    }
} // UI
