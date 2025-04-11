#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>

#include "UI/Text.h"
#include "Menus/StartMenu.h"
#include "Menus/GameMenu.h"

void App::Start() {
    LOG_TRACE("Start");

    // Add text
    // m_Text = std::make_shared<Text>("Start", 50);
    // m_Root.AddChild(m_Text);

    // Add background image
    m_BackgroundImage = std::make_shared<BackgroundImage>();
    m_Root.AddChild(m_BackgroundImage);

    // Add all menu
    m_Menu = std::make_shared<StartMenu>(&m_Root);
    // m_Root.AddChild(m_Menu);

    // Set App State
    m_CurrentState = State::UPDATE;

    // Open start menu ( the first menu
    m_Menu->Open();
}

void App::Update() {
    //TODO: do your things here and delete this line <3

    m_Menu->Update(this);

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

void App::ChangeMenu(Menu::Screen screen) {
    m_Menu->Close();
    switch (screen) {
        case Menu::Screen::START_MENU:
            m_Menu = std::make_shared<StartMenu>(&m_Root);
            m_BackgroundImage->SetImage(RESOURCE_DIR"/image/background.png");
            break;
        case Menu::Screen::GAME_MENU:
            m_Menu = std::make_shared<GameMenu>(&m_Root);
            m_BackgroundImage->SetImage(RESOURCE_DIR"/image/background.bmp");
            break;
        case Menu::Screen::STORE_MENU:
            break;
    }
    m_Menu->Open();
}

void App::End() {
    // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
