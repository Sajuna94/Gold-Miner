#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "BackgroundImage.h"
#include "Menu.h"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    void ChangeMenu(Menu::Screen screen);

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }

private:
    void ValidTask();

    Util::Renderer m_Root;
    State m_CurrentState = State::START;

    // std::shared_ptr<Text> m_Text;
    std::shared_ptr<BackgroundImage> m_BackgroundImage;
    std::shared_ptr<Menu> m_Menu;
};

#endif
