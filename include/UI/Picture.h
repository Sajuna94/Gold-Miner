//
// Created by ianli on 2025/3/28.
//

#ifndef PICTURE_H
#define PICTURE_H
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace UI
{
    class Picture final : public Util::GameObject
    {
    public:
        explicit Picture(const std::string& imagePath, const glm::vec2 position) : GameObject(
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
        void SetPosition(const glm::vec2 position)
        {
            m_Transform.translation = position;
        }
    };
}


#endif //PICTURE_H
