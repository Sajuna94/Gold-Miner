#include "Menus/GameMenu.h"
#include "App.hpp"
#include "UI/Text.h"
#include "Util/Input.hpp"
#include <iostream>

#include "Ores/Gold.h"
#include "Ores/Rock.h"

#define HALF_WINDOW_WIDTH (WINDOW_WIDTH / 2)
#define HALF_WINDOW_HEIGHT (WINDOW_HEIGHT / 2)

namespace DefaultPosition
{
    constexpr glm::vec2 Miner = {5.5, 255};
    constexpr glm::vec2 Pickaxe = {0, 229};
    constexpr glm::vec2 MoneyText = {-495, HALF_WINDOW_HEIGHT - 89};
    constexpr glm::vec2 LevelText = {515, HALF_WINDOW_HEIGHT - 48};
}

void GameMenu::Open()
{
    printf("[~] Open GameMenu\n");

    m_Miner = std::make_shared<Miner>(DefaultPosition::Miner);
    m_Root->AddChild(m_Miner);

    m_Pickaxe = std::make_shared<Pickaxe>(DefaultPosition::Pickaxe);
    m_Pickaxe->SetPivot({0, 6});
    m_Pickaxe->SetHitBox({0, 0}, {30, 15});
    m_Root->AddChild(m_Pickaxe);

    m_Rope = std::make_shared<UI::Picture>(RESOURCE_DIR"/Color/black.png", DefaultPosition::Pickaxe);
    m_Rope->SetScaleSize({3, 3});
    m_Rope->SetZIndex(40);
    m_Root->AddChild(m_Rope);

    m_RedLine = std::make_shared<UI::Picture>(RESOURCE_DIR"/Color/red.png", DefaultPosition::Pickaxe);
    m_RedLine->SetScaleSize({1, 1500});
    m_RedLine->SetZIndex(39);
    m_Root->AddChild(m_RedLine);

    m_TimerText = std::make_shared<UI::Text>("TIME", 20);
    m_TimerText->SetPosition({HALF_WINDOW_WIDTH - m_TimerText->GetScaledSize().x, HALF_WINDOW_HEIGHT - 20});
    m_Root->AddChild(m_TimerText);

    m_MoneyText = std::make_shared<UI::Text>("0", 34);
    m_MoneyText->SetPosition(DefaultPosition::MoneyText);
    m_MoneyText->SetColor(Util::Color::FromRGB(110, 72, 34));
    m_Root->AddChild(m_MoneyText);

    m_LevelText = std::make_shared<UI::Text>("1", 34);
    m_LevelText->SetPosition(DefaultPosition::LevelText);
    m_LevelText->SetColor(Util::Color::FromRGB(110, 72, 34));
    m_Root->AddChild(m_LevelText);

    while (m_OreList.size() < 20)
    {
        int randomIndex = rand() % static_cast<int>(Ore::Type::Count);
        GenerateOre(static_cast<Ore::Type>(randomIndex));
    }
    for (auto& ore : m_OreList)
    {
        m_Root->AddChild(ore);
    }

    printf("WINDOW_SIZE: %d, %d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameMenu::Update(App* app)
{
    const float dt = Util::Time::GetDeltaTimeMs() / 1000.0f;
    m_TimerText->SetText("FPS: " + std::to_string(1.0f / dt));

    UpdatePickaxe(dt);
}

void GameMenu::UpdatePickaxe(const float dt)
{
    m_Rope->SetScaleSize({3, glm::length(DefaultPosition::Pickaxe - m_Pickaxe->GetPosition())});
    m_Rope->SetPosition((DefaultPosition::Pickaxe + m_Pickaxe->GetPosition()) * 0.5f);
    m_RedLine->SetRotation(m_Pickaxe->GetRotation());

    switch (m_Pickaxe->GetState())
    {
    case Pickaxe::State::STOP:
        if (!Util::Input::IsKeyPressed(Util::Keycode::SPACE))
            m_Pickaxe->UpdateAngle(dt);
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB))
            m_Pickaxe->Throw();
        break;
    case Pickaxe::State::THROWN:
        m_Pickaxe->UpdateMove(dt);
        m_Rope->SetRotation(m_Pickaxe->GetRotation());

        if (IsOutOfWindow(*m_Pickaxe))
            m_Pickaxe->Return();
        for (const auto& ore : m_OreList)
        {
            if (m_Pickaxe->IsOverlappingWith(*ore))
            {
                m_Pickaxe->Return();
                m_Pickaxe->SetDragOre(ore);
                break;
            }
        }
        break;
    case Pickaxe::State::RETURN:
        m_Pickaxe->UpdateMove(dt);
        if (m_Pickaxe->GetPosition().y > DefaultPosition::Pickaxe.y)
        {
            m_Pickaxe->Stop();
            m_Pickaxe->SetPosition(DefaultPosition::Pickaxe);

            if (const auto& ore = m_Pickaxe->TakeDragOre())
            {
                // Get money
                money += ore->GetMoney();
                m_MoneyText->SetText(std::to_string(money));
                printf("[$] Get %d$\n", ore->GetMoney());
                // Remove Ore
                m_OreList.remove(ore);
                m_Root->RemoveChild(ore);
            }
        }
        break;
    }
}

void GameMenu::Close()
{
    printf("[~] Close GameMenu\n");

    for (auto& ore : m_OreList)
    {
        m_Root->RemoveChild(ore);
    }
}

void GameMenu::GenerateOre(const Ore::Type type)
{
    std::shared_ptr<Ore> ore;
    switch (type)
    {
    case Ore::Type::ROCK: ore = std::make_shared<Rock>();
        break;
    case Ore::Type::GOLD: ore = std::make_shared<Gold>();
        break;
    case Ore::Type::DIAMOND: ore = std::make_shared<Diamond>();
        break;
    default: break;
    }

    while (true)
    {
        ore->SetPosition({
            RandInRange(-HALF_WINDOW_WIDTH, HALF_WINDOW_WIDTH),
            RandInRange(-HALF_WINDOW_HEIGHT, HALF_WINDOW_HEIGHT - 250)
        });

        if (IsOutOfWindow(*ore))
            continue;
        if (std::any_of(m_OreList.begin(), m_OreList.end(),
                        [&](const auto& other) { return other->IsOverlappingWith(*ore); }))
            continue;

        m_OreList.push_back(ore);
        break;
    }
}


bool GameMenu::IsOutOfWindow(const Util::GameObject& object)
{
    const glm::vec2 centerPt = object.GetTransform().translation;
    const glm::vec2 halfEdgeSize = (glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) - object.GetScaledSize()) * 0.5f;
    return
        any(lessThan(centerPt, -halfEdgeSize)) ||
        any(greaterThan(centerPt, halfEdgeSize));
}
