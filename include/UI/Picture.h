#ifndef PICTURE_H
#define PICTURE_H
#include "Core/Interfaces/IMoveable.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace UI
{
    class Picture final : virtual public Util::GameObject, public IMoveable
    {
    public:
        explicit Picture(const std::string& imagePath, const float zIndex) : GameObject(
            std::make_unique<Util::Image>(imagePath), zIndex)
        {
        }

        void SetScaleSize(const glm::vec2 scale) { m_Transform.scale = scale; }

        void SetRotation(const float rotation) { m_Transform.rotation = rotation; }

        void SetImage(const std::string& imagePath) const
        {
            auto const temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
            temp->SetImage(imagePath);
        }
    };
}


#endif //PICTURE_H
