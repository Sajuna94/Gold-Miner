#ifndef TEXT_H
#define TEXT_H

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

class Text : public Util::GameObject {
public:
    Text(const std::string &text, const int size) : GameObject(
            std::make_unique<Util::Text>(RESOURCE_DIR"/Font/Inkfree.ttf", size, text, Util::Color::FromName(Util::Colors::WHITE)),
            100
    ) {
        m_Transform.translation = { 0.0F, 0.0F };
    }

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }
};

#endif //TEXT_H
