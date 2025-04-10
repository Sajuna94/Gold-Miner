#ifndef MENU_H
#define MENU_H

#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"

class Menu : public Util::GameObject {
public:
    enum class Screen {
        START_MENU,
        STORE_MENU,
        GAME_MENU,
    };

    Util::Renderer *m_Root;

    explicit Menu(Util::Renderer *root) { m_Root = root; }

    virtual void Open() = 0;

    virtual void Update(App *app) = 0;

    virtual void Close() = 0;
};


#endif //MENU_H
