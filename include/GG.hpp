//
// Created by ianli on 2025/3/7.
//

#ifndef GG_HPP
#define GG_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class GG : public Util::GameObject
{
public:
    // 修改建構函式，使其可以接受圖片路徑
    GG(const std::string& imagePath)
        : GameObject(std::make_unique<Util::Image>(imagePath), 10)
    {
    }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }
};

#endif //GG_HPP
