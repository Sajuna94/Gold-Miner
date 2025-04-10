#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>
#include "Menu.h"

#include "Util/Text.hpp"
#include "Text.h"

void App::Start() {
    LOG_TRACE("Start");

    m_Text = std::make_shared<Text>("Start", 50);
    m_Root.AddChild(m_Text);




    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3

    switch (m_CurrentScreen) {
        case Screen::START_MENU: m_startMenu->Update(); break;
        case Screen::GAME_MENU: m_startMenu->Update(); break;
        case Screen::STORE_MENU: m_startMenu->Update(); break;
    }








    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
