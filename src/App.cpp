#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>

#include "Screen/GameScene.h"

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    m_CurrentScreen = std::make_shared<Screen::GameScene>();
    m_CurrentScreen->Init(m_Root);
}

void App::Update() {
    //TODO: do your things here and delete this line <3
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
    m_CurrentScreen->Update();
}

void App::End() {
    // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

void App::ValidTask() {
    // LOG_TRACE("ValidTask");
}

