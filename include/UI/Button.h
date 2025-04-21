#ifndef BUTTON_H
#define BUTTON_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "IClickable.h"
#include "Picture.h"

namespace UI
{
    class Button final : public Util::GameObject, public IClickable
    {
    public:
        explicit Button(const std::string& imagePath)
            : GameObject(std::make_unique<Util::Image>(imagePath), 10)
        {
        }

        void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
        [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

        void Click() override;

        [[nodiscard]] bool IsClicked() override;

        [[nodiscard]] bool OnHover() const override;

        void SetImage(const std::string& imagePath) const
        {
            auto const temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
            temp->SetImage(imagePath);
        }

    private:
        bool waitingMouseUp = false;
    };
}

#endif //BUTTON_H
