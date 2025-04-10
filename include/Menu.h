//
// Created by ianli_7p249vy on 2025/3/28.
//

#ifndef MENU_H
#define MENU_H
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Button.h"


class Menu : public Util::GameObject {
public:
    Menu(Util::Renderer *m_Root);

    void Update();
private:
    std::shared_ptr<Button> m_startButton;
};



#endif //MENU_H
