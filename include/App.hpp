#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Button.h"
#include "Text.h"
#include "Menu.h"



class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    enum class Screen {
        START_MENU,
        STORE_MENU,
        GAME_MENU,
    };



    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    Util::Renderer m_Root;


    State m_CurrentState = State::START;
    Screen m_CurrentScreen = Screen::START_MENU;

    std::shared_ptr<Text> m_Text;

    std::shared_ptr<Menu> m_startMenu;
};

#endif
