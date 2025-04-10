#include "UI/Button.h"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void UI::Button::Click()
{
}

bool UI::Button::IsClicked()
{
    if (!waitingMouseUp && Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && OnHover())
    {
        this->waitingMouseUp = true;
    }
    if (waitingMouseUp && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && OnHover())
    {
        this->waitingMouseUp = false;
        return OnHover();
    }
    return false;
}

bool UI::Button::OnHover() const
{
    glm::vec2 const cursorPos = Util::Input::GetCursorPosition();
    glm::vec2 const buttonPos = this->GetPosition();
    glm::vec2 const buttonSize = this->GetScaledSize();

    return !(
        cursorPos.x < buttonPos.x - buttonSize.x / 2 ||
        cursorPos.x > buttonPos.x + buttonSize.x / 2 ||
        cursorPos.y < buttonPos.y - buttonSize.y / 2 ||
        cursorPos.y > buttonPos.y + buttonSize.y / 2);
}
