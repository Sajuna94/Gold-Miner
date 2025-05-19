#ifndef PICTURE_H
#define PICTURE_H
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace UI {
    class Picture final : public Util::GameObject {
    public:
        explicit Picture(const std::string &imagePath, glm::vec2 position = {});

        void FullScreen();

    private:
        std::shared_ptr<Util::Image> m_Image;
    };
} // UI

#endif //PICTURE_H
