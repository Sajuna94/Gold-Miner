#ifndef TEXT_H
#define TEXT_H

#include "Core/Interfaces/IMoveable.h"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

namespace UI
{
    class Text final : virtual public Util::GameObject, public IMoveable
    {
    public:
        enum class Type { LEFT, MID, RIGHT };

    private:
        Type m_CurrentType = Type::MID;
        std::string m_Text;

    public:
        Text(const std::string& text, const int size)
            : GameObject(
                  std::make_unique<Util::Text>(RESOURCE_DIR"/Font/Caveat-Bold.ttf", size, text,
                                               Util::Color::FromName(Util::Colors::WHITE))
                  ,
                  100
              ),
              m_Text(text)
        {
        }

        void SetText(const std::string& text)
        {
            m_Text = text;
            const float tempWidth = GetScaledSize().x;

            const auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
            temp->SetText(text);

            switch (m_CurrentType)
            {
            case Type::LEFT:
                m_Transform.translation = GetPosition() + glm::vec2((GetScaledSize().x - tempWidth) * 0.5f, 0);
                break;
            default: break;
            }
        }

        [[nodiscard]] std::string GetText() const { return m_Text; }

        void SetType(const Type type)
        {
            m_CurrentType = type;
        }

        void SetColor(const Util::Color color) const
        {
            const auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
            temp->SetColor(color);
        }
    };
}

#endif //TEXT_H
