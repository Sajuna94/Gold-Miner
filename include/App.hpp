#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"
#include "UI/Text.h"
#include "BackgroundImage.h"
#include "Menus/GameMenu.h"
#include "Menus/StartMenu.h"

class App
{
public:
    enum class State
    {
        START,
        UPDATE,
        END,
    };

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }
    std::shared_ptr<BackgroundImage> GetBackgroundImage() const { return m_BackgroundImage; }
    std::shared_ptr<GameMenu> GetGameMenu() const { return m_GameMenu; }
    Util::Renderer* GetRendererRoot() { return &m_Root; };

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    Util::Renderer m_Root;
    State m_CurrentState = State::START;


    // std::shared_ptr<Text> m_Text;
    std::shared_ptr<BackgroundImage> m_BackgroundImage;
    std::shared_ptr<StartMenu> m_StartMenu;
    std::shared_ptr<GameMenu> m_GameMenu;
};

#endif
