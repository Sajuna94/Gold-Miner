#include "UI/Button.h"

#include "Util/Input.hpp"

namespace UI {
    Button::Button(const std::string &imagePath)
        : m_Image(std::make_shared<Util::Image>(imagePath)) {
        SetDrawable(m_Image);
    }

    bool Button::OnHover() const {
        return rect(m_Transform.translation, GetScaledSize()).contains(Util::Input::GetCursorPosition());
    }

    bool Button::OnClick() const {
        return Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && OnHover();
    }

    void Button::SetImage(const std::string &imagePath) const {
        m_Image->SetImage(imagePath);
    }
} // UI
