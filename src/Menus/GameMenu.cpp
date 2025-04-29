#include "Menus/GameMenu.h"
#include "App.hpp"
#include "Util/Input.hpp"

#include <iostream>

constexpr int HALF_WINDOW_WIDTH = WINDOW_WIDTH / 2;
constexpr int HALF_WINDOW_HEIGHT = WINDOW_HEIGHT / 2;

namespace DefaultPosition
{
    constexpr glm::vec2 MoneyText = {-495, HALF_WINDOW_HEIGHT - 89};
    constexpr glm::vec2 AddedMoneyText = {0, 100};
    constexpr glm::vec2 LastAddedMoneyText = {0, 100};
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

    // m_AddedMoneyText = std::make_shared<UI::Text>("000", 90);
    // m_AddedMoneyText->SetPosition(DefaultPosition::AddedMoneyText);
    // m_AddedMoneyText->SetColor(Util::Color::FromRGB(69, 95, 47));
    // m_AddedMoneyText->SetVisible(false);
    // AddChild(m_AddedMoneyText);

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

    AnimeAddedMoney(dt);

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
        {
            m_MoneyEffectSound->Play();
            auto lastAddedMoneyText = std::make_shared<UI::Text>("000", 90);
            lastAddedMoneyText->SetText(std::to_string(m_GameLogic->GetLastAddedMoney()));
            lastAddedMoneyText->SetPosition(DefaultPosition::LastAddedMoneyText);
            lastAddedMoneyText->SetColor(Util::Color::FromRGB(69, 95, 47));
            AddChild(lastAddedMoneyText);
            m_TextAnimeBuffer.insert(
                std::make_shared<std::pair<float, std::shared_ptr<UI::Text>>>(0.0f, lastAddedMoneyText));
            return;
        }
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

void GameMenu::AnimeAddedMoney(const float dt)
{
    const auto copyBuffer = m_TextAnimeBuffer;

    for (auto& animeData : copyBuffer)
    {
        auto& elapsedTime = animeData->first;
        auto& moneyText = animeData->second;

        if (elapsedTime <= 0.5f)
        {
            elapsedTime += dt;
            continue;
        }

        constexpr glm::vec2 startPos = DefaultPosition::AddedMoneyText;
        constexpr glm::vec2 targetPos = DefaultPosition::MoneyText + glm::vec2(120, 0);
        const glm::vec2 curPos = moneyText->GetPosition();

        constexpr glm::vec2 totalVec = targetPos - startPos;
        const glm::vec2 movedVec = curPos - startPos;

        float progress = glm::dot(movedVec, totalVec) / glm::dot(totalVec, totalVec);
        progress = glm::clamp(progress, 0.0f, 1.0f); // 避免超過

        if (progress >= 1.0f)
        {
            if (elapsedTime <= 1.5f)
            {
                elapsedTime += dt;
                continue;
            }
            m_MoneyText->SetText(std::to_string(
                    std::stoi(moneyText->GetText()) +
                    std::stoi(m_MoneyText->GetText()))
            );
            RemoveChild(moneyText);
            m_TextAnimeBuffer.erase(animeData);
            continue;
        }

        // Compute scale size
        const float size = glm::mix(1.0f, 0.7f, progress);
        moneyText->m_Transform.scale = glm::vec2(size);

        const glm::vec2 direction = glm::normalize(totalVec);
        constexpr float speed = 300.0f;
        moneyText->Move(direction * speed, dt);
    }
}


// bool GameMenu::IsOutOfWindow(const GameObject& object)
// {
//     const glm::vec2 centerPt = object.GetTransform().translation;
//     const glm::vec2 halfEdgeSize = (glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) - object.GetScaledSize()) * 0.5f;
//     return
//         any(lessThan(centerPt, -halfEdgeSize)) ||
//         any(greaterThan(centerPt, halfEdgeSize));
// }
