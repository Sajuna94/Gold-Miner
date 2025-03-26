#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>

#include "Util/Text.hpp"
#include "Text.h"

void App::Start() {
    LOG_TRACE("Start");

    m_startButton = std::make_shared<Button>(RESOURCE_DIR"/gold_miner_source/button-sheet0.png");
    m_startButton->SetPosition({0.5f, 0.5f});

    m_Root.AddChild(m_startButton);

    m_Text = std::make_shared<Text>("Start", 50);
    m_Root.AddChild(m_Text);




    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3
    if (m_startButton->CheckClick()) {
        std::cout << "startButton Pressed" << std::endl;

        m_CurrentScreen = Screen::GAME_MENU;
        // ChangeScreen(Screen::GAME_MENU);
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
