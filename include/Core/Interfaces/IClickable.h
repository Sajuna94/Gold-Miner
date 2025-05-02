#ifndef ICLICKABLE_H
#define ICLICKABLE_H
#include "Util/Input.hpp"

class IClickable
{
    bool m_WaitingKeyUp = false;

public:
    virtual ~IClickable() = default;

    // check mouse was click the button
    [[nodiscard]] virtual bool IsClicked()
    {
        if (!m_WaitingKeyUp && Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && OnHover())
        {
            m_WaitingKeyUp = true;
            return false;
        }
        if (m_WaitingKeyUp && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && OnHover())
        {
            m_WaitingKeyUp = false;
            return true;
        }
        return false;
    }

    // check mouse hover on the UI
    [[nodiscard]] virtual bool OnHover() const = 0;
};

#endif //ICLICKABLE_H
