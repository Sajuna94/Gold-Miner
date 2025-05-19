#ifndef BUTTON_H
#define BUTTON_H
#include "Core/Math/Shape.h"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace UI {
    class Button final : public Util::GameObject {
    public:
        explicit Button(const std::string &imagePath);

        [[nodiscard]] bool OnHover() const;

        [[nodiscard]] bool OnClick() const;

        void SetImage(const std::string &imagePath) const;

    private:
        const std::shared_ptr<Util::Image> m_Image;
    };
} // UI

#endif //BUTTON_H
