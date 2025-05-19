#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

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

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }

private:
    void ValidTask();

    Util::Renderer m_Root;
    State m_CurrentState = State::START;
};

#endif
