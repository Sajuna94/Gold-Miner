#ifndef MENU_H
#define MENU_H

#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"

class Menu : public Util::GameObject
{
private:
    enum class Screen
    {
        START_MENU,
        STORE_MENU,
        GAME_MENU,
    };

public:
    virtual void Open(Util::Renderer* m_Root) = 0;

    virtual void Update(App* app) = 0;

    virtual void Close(Util::Renderer* m_Root) const = 0;
};


#endif //MENU_H
