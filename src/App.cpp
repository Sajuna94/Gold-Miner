#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>

#include "Util/Text.hpp"
#include "../include/UI/Text.h"

void App::Start()
{
    LOG_TRACE("Start");

    // Add text
    // m_Text = std::make_shared<Text>("Start", 50);
    // m_Root.AddChild(m_Text);

    // Add background image
    m_BackgroundImage = std::make_shared<BackgroundImage>();
    m_Root.AddChild(m_BackgroundImage);

    // Add all menu
    m_StartMenu = std::make_shared<StartMenu>(&m_Root);
    m_Root.AddChild(m_StartMenu);

    m_GameMenu = std::make_shared<GameMenu>();
    m_Root.AddChild(m_GameMenu);

    // Set App State
    m_CurrentState = State::UPDATE;

    // Open start menu ( the first menu
    m_StartMenu->Open();
}

void App::Update()
{
    //TODO: do your things here and delete this line <3

    switch (m_BackgroundImage->GetCurrentScreen())
    {
    case BackgroundImage::Screen::START_MENU:
        m_StartMenu->Update(this);
        break;
    case BackgroundImage::Screen::GAME_MENU:
        m_GameMenu->Update(this);
        break;
    case BackgroundImage::Screen::STORE_MENU:
        break;
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit())
    {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::End()
{
    // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
