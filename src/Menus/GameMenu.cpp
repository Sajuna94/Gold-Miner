#include "Menus/GameMenu.h"
#include "App.hpp"
#include "Util/Input.hpp"

#include <iostream>

constexpr int HALF_WINDOW_WIDTH = WINDOW_WIDTH / 2;
constexpr int HALF_WINDOW_HEIGHT = WINDOW_HEIGHT / 2;

namespace DefaultPosition
{
    constexpr glm::vec2 MoneyText = {-495, HALF_WINDOW_HEIGHT - 89};
    constexpr glm::vec2 TargetText = {-495, HALF_WINDOW_HEIGHT - 137.5};
    constexpr glm::vec2 LevelText = {520, HALF_WINDOW_HEIGHT - 49};
    constexpr glm::vec2 CountDownText = {505, HALF_WINDOW_HEIGHT - 106.5};
}

void GameMenu::Open()
{
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/game_background.png"));

    printf("[~] Open GameMenu\n");

    m_GameLogic = std::make_shared<GameLogic>();

    m_FPSText = std::make_shared<UI::Text>("TIME", 20);
    m_FPSText->SetPosition({HALF_WINDOW_WIDTH - m_FPSText->GetScaledSize().x, HALF_WINDOW_HEIGHT - 20});
    AddChild(m_FPSText);

    m_MoneyText = std::make_shared<UI::Text>("0", 34);
    m_MoneyText->SetPosition(DefaultPosition::MoneyText);
    m_MoneyText->SetColor(Util::Color::FromRGB(110, 72, 34));
    AddChild(m_MoneyText);

    m_TargetText = std::make_shared<UI::Text>("0", 34);
    m_TargetText->SetPosition(DefaultPosition::TargetText);
    m_TargetText->SetColor(Util::Color::FromRGB(110, 72, 34));
    AddChild(m_TargetText);

    m_LevelText = std::make_shared<UI::Text>("0", 34);
    m_LevelText->SetPosition(DefaultPosition::LevelText);
    m_LevelText->SetColor(Util::Color::FromRGB(110, 72, 34));
    AddChild(m_LevelText);

    m_TimeLeftText = std::make_shared<UI::Text>("0", 34);
    m_TimeLeftText->SetPosition(DefaultPosition::CountDownText);
    m_TimeLeftText->SetColor(Util::Color::FromRGB(110, 72, 34));
    AddChild(m_TimeLeftText);

    printf("WINDOW_SIZE: %d, %d\n", WINDOW_WIDTH, WINDOW_HEIGHT);

    m_GameLogic->GameStart();
}

void GameMenu::Update(App* app)
{
    const float dt = Util::Time::GetDeltaTimeMs() / 1000.0f;
    m_FPSText->SetText("FPS: " + std::to_string(1.0f / dt));

    InputState input;
    input.MoveLeftMiner = Util::Input::IsKeyPressed(Util::Keycode::A);
    input.MoveRightMiner = Util::Input::IsKeyPressed(Util::Keycode::D);
    input.ThrowPickaxe = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);
    input.ReturnPickaxe = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB);

    // if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))
    //     for (const auto& child : GetChildren())
    //         if (const auto& entity = std::dynamic_pointer_cast<Entity>(child))
    //             entity->Move({-1, 0});

    if (m_GameLogic->GetState() == GameLogic::State::RUNNING)
        m_GameLogic->Update(dt, input);
    for (const auto& command : m_GameLogic->ExtractCommands())
        HandleCommand(command);
}

void GameMenu::HandleCommand(const GameLogic::CommandType command)
{
    switch (command)
    {
    case GameLogic::CommandType::AddChildren:
        for (const auto& child : m_GameLogic->ExtractAddedChildren())
            AddChild(child);
        return;
    case GameLogic::CommandType::RemoveChildren:
        for (const auto& child : m_GameLogic->ExtractRemovedChildren())
            RemoveChild(child);
        return;
    case GameLogic::CommandType::AddMoney:
        m_MoneyEffectSound->Play();
        m_MoneyText->SetText(std::to_string(m_GameLogic->GetMoney()));
        return;
    case GameLogic::CommandType::UpdateTimeLeft:
        m_TimeLeftText->SetText(std::to_string(m_GameLogic->GetTimeLeft()));
    }
}

void GameMenu::Close()
{
    printf("[~] Close GameMenu\n");
    auto children = GetChildren();
    for (const auto& child : children)
        RemoveChild(child);
}

// bool GameMenu::IsOutOfWindow(const GameObject& object)
// {
//     const glm::vec2 centerPt = object.GetTransform().translation;
//     const glm::vec2 halfEdgeSize = (glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) - object.GetScaledSize()) * 0.5f;
//     return
//         any(lessThan(centerPt, -halfEdgeSize)) ||
//         any(greaterThan(centerPt, halfEdgeSize));
// }
