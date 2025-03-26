#ifndef BUTTON_H
#define BUTTON_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "IClickable.h"

class Button : public Util::GameObject, public IClickable {
private:
    bool waitingMouseUp = false;
public:
    explicit Button(const std::string &imagePath)
        : GameObject(std::make_unique<Util::Image>(imagePath), 10) {
    }

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }
    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    void Click() override;
    [[nodiscard]] bool CheckClick() override;
    [[nodiscard]] bool OnHover() const override;
};


#endif //BUTTON_H
