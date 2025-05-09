#include "UI/Button.h"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

bool UI::Button::OnHover() const
{
    glm::vec2 const cursorPos = Util::Input::GetCursorPosition();
    glm::vec2 const buttonPos = m_Transform.translation;
    glm::vec2 const buttonSize = GetScaledSize();

    return !(
        cursorPos.x < buttonPos.x - buttonSize.x / 2 ||
        cursorPos.x > buttonPos.x + buttonSize.x / 2 ||
        cursorPos.y < buttonPos.y - buttonSize.y / 2 ||
        cursorPos.y > buttonPos.y + buttonSize.y / 2);
}
