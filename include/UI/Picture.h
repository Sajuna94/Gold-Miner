#ifndef PICTURE_H
#define PICTURE_H
#include "Core/Interfaces/IMoveable.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace UI
{
    class Picture final : public Util::GameObject, public IMoveable
    {
    public:
        explicit Picture(const std::string& imagePath, const int zIndex) : GameObject(
            std::make_unique<Util::Image>(imagePath), zIndex)
        {
        }

        void SetScaleSize(const glm::vec2 scale) { m_Transform.scale = scale; }

        // Interface IMoveable
        [[nodiscard]] glm::vec2 GetPosition() const override { return m_Transform.translation; }
        void SetPosition(const glm::vec2& position) override { m_Transform.translation = position; }
        void SetRotation(const float rotation) override { m_Transform.rotation = rotation; }

        void SetImage(const std::string& imagePath) const
        {
            auto const temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
            temp->SetImage(imagePath);
        }
    };
}


#endif //PICTURE_H
