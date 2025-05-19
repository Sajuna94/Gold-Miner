#ifndef PICTURE_H
#define PICTURE_H
#include "config.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace UI {
    class Picture final : public Util::GameObject {
    public:
        enum class Align { TOP, LEFT, BOTTOM, RIGHT };

        explicit Picture(const std::string &path, glm::vec2 position = {});

        void FullScreen(const glm::vec2 &view = {WINDOW_WIDTH, WINDOW_HEIGHT});

        void AlignTo(const Align &align, const glm::vec2 &view = {WINDOW_WIDTH, WINDOW_HEIGHT});

    private:
        std::shared_ptr<Util::Image> m_Image;
    };
} // UI

#endif //PICTURE_H
