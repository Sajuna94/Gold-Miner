//
// Created by ianli on 2025/3/28.
//

#ifndef PICTURE_H
#define PICTURE_H
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Picture final : public Util::GameObject {
    explicit Picture(const std::string &imagePath, glm::vec2 position) : GameObject(
        std::make_unique<Util::Image>(RESOURCE_DIR + imagePath), 0) {
        m_Transform.translation = position;
    }
};


#endif //PICTURE_H
