#include "App.hpp"
#include "Util/Logger.hpp"
#include <iostream>

#include "UI/Text.h"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Menus/StartMenu.h"
#include "Menus/GameMenu.h"
#include "Menus/ShopMenu.h"

void App::Start()
{
    LOG_TRACE("Start");

    // Add Menu
    m_Menu = std::make_shared<StartMenu>();
    m_Root.AddChild(m_Menu);

    // Set App State
    m_CurrentState = State::UPDATE;

    // Open Start menu
    m_Menu->Open();
}

void App::Update()
{
    //TODO: do your things here and delete this line <3
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
    m_Menu->Update(this);
}

void App::ChangeMenu(const Menu::Screen screen)
{
    m_Menu->Close();
    m_Root.RemoveChild(m_Menu);
    switch (screen)
    {
    case Menu::Screen::START_MENU:
        m_Menu = std::make_shared<StartMenu>();
        break;
    case Menu::Screen::GAME_MENU:
        m_Menu = std::make_shared<GameMenu>(m_CurrentLevel);
        break;
    case Menu::Screen::STORE_MENU:
        m_Menu = std::make_shared<ShopMenu>(m_CurrentLevel);
        m_CurrentLevel += 1;
        break;
    }
    m_Root.AddChild(m_Menu);
    m_Menu->Open();
}

void App::End()
{
    // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
