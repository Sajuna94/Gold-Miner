#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>

#include "Core/ScreenManager.h"
#include "Screen/GameScene.h"
#include "Screen/StartMenu.h"

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;

    glDisable(GL_DEBUG_OUTPUT);

    ScreenManager::Init(m_Root);
    ScreenManager::NextScreen(std::make_unique<Screen::StartMenu>());
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

    ScreenManager::UpdateScreen();
    Logger::Flush();
}

void App::End() {
    // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

void App::ValidTask() {
    LOG_TRACE("ValidTask");
}

