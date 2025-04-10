#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "config.hpp"

class BackgroundImage final : public Util::GameObject {
public:
    BackgroundImage() : GameObject(
        std::make_unique<Util::Image>(RESOURCE_DIR"/image/background.png"), -10) {
        m_Transform.translation = {0.0F, 0.0F};
        SetImage(RESOURCE_DIR"/image/background.png");
    }

    void SetImage(const std::string &imagePath) {
        auto const temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(imagePath);

        glm::vec2 const size = temp->GetSize();
        m_Transform.scale = {WINDOW_WIDTH / size.x, WINDOW_HEIGHT / size.y};
    };
};


#endif //BACKGROUNDIMAGE_H
