#ifndef MENU_H
#define MENU_H

#include "config.hpp"
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Util/Image.hpp"

class Menu : public Util::GameObject
{
public:
    enum class Screen
    {
        START_MENU,
        STORE_MENU,
        GAME_MENU,
    };

    explicit Menu(const std::string& imagePath, const glm::vec2 position = {0, 0}) :
        GameObject(std::make_unique<Util::Image>(imagePath), -5)
    {
        m_Transform.translation = position;

        glm::vec2 const size = m_Drawable->GetSize();
        m_Transform.scale = {WINDOW_WIDTH / size.x, WINDOW_HEIGHT / size.y};
    }

    virtual void Open() = 0;
    virtual void Update(App* app) = 0;
    virtual void Close() = 0;
};


#endif //MENU_H
