//
// Created by ianli on 2025/3/28.
//

#ifndef PICTURE_H
#define PICTURE_H
#include "IMoveable.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace UI
{
    class Picture final : public Util::GameObject, public IMoveable
    {
    public:
        explicit Picture(const std::string& imagePath, const glm::vec2 position = {0, 0}) : GameObject(
            std::make_unique<Util::Image>(imagePath), 5)
        {
            m_Transform.translation = position;
        }

        void SetScaleSize(const glm::vec2 scale)
        {
            m_Transform.scale = scale;
        }

        void SetRotation(const float rotation)
        {
            m_Transform.rotation = rotation;
        }

        [[nodiscard]] glm::vec2 GetPosition() const override { return m_Transform.translation; }
        void SetPosition(const glm::vec2& position) override { m_Transform.translation = position; }

        void SetImage(const std::string& imagePath) const
        {
            auto const temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
            temp->SetImage(imagePath);
        }
    };
}


#endif //PICTURE_H
