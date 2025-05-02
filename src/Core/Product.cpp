#include "Core/Product.h"

#include "Util/Input.hpp"

bool Product::IsClicked()
{
}

bool Product::OnHover() const
{
    glm::vec2 const cursorPos = Util::Input::GetCursorPosition();
    glm::vec2 const buttonPos = m_Picture->m_Transform.translation;
    glm::vec2 const buttonSize = m_Picture->GetScaledSize();

    return !(
        cursorPos.x < buttonPos.x - buttonSize.x / 2 ||
        cursorPos.x > buttonPos.x + buttonSize.x / 2 ||
        cursorPos.y < buttonPos.y - buttonSize.y / 2 ||
        cursorPos.y > buttonPos.y + buttonSize.y / 2);
}
