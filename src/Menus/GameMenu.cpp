#include "Menus/GameMenu.h"
#include "App.hpp"
#include "UI/Text.h"
#include "Util/Input.hpp"
#include <iostream>

#include "Ores/Gold.h"
#include "Ores/Rock.h"

#define HALF_WINDOW_WIDTH (WINDOW_WIDTH / 2)
#define HALF_WINDOW_HEIGHT (WINDOW_HEIGHT / 2)

#define MAX_ORE_COUNT 20

namespace DefaultPosition
{
    constexpr glm::vec2 Miner = {5.5, 255};
    constexpr glm::vec2 MoneyText = {-495, HALF_WINDOW_HEIGHT - 89};
    constexpr glm::vec2 LevelText = {515, HALF_WINDOW_HEIGHT - 48};
}

void GameMenu::Open()
{
    SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/Background/game_background.png"));

    printf("[~] Open GameMenu\n");

    m_Miner = std::make_shared<Miner>(DefaultPosition::Miner);
    AddChild(m_Miner);

    m_TimerText = std::make_shared<UI::Text>("TIME", 20);
    m_TimerText->SetPosition({HALF_WINDOW_WIDTH - m_TimerText->GetScaledSize().x, HALF_WINDOW_HEIGHT - 20});
    AddChild(m_TimerText);

    m_MoneyText = std::make_shared<UI::Text>("0", 34);
    m_MoneyText->SetPosition(DefaultPosition::MoneyText);
    m_MoneyText->SetColor(Util::Color::FromRGB(110, 72, 34));
    AddChild(m_MoneyText);

    m_LevelText = std::make_shared<UI::Text>("1", 34);
    m_LevelText->SetPosition(DefaultPosition::LevelText);
    m_LevelText->SetColor(Util::Color::FromRGB(110, 72, 34));
    AddChild(m_LevelText);


    for (int i = 0; i < MAX_ORE_COUNT; i++)
        GenerateOre(static_cast<Ore::Type>(rand() % static_cast<int>(Ore::Type::Count)));

    printf("WINDOW_SIZE: %d, %d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameMenu::Update(App* app)
{
    const float dt = Util::Time::GetDeltaTimeMs() / 1000.0f;
    m_TimerText->SetText("FPS: " + std::to_string(1.0f / dt));


    UpdateGameLogic(dt);
    m_Miner->Update(dt);
}

void GameMenu::UpdateGameLogic(const float dt)
{
    switch (const auto pickaxe = m_Miner->GetPickaxe(); pickaxe->GetState())
    {
    case Pickaxe::State::STOP:
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB))
            m_Miner->ThrowPickaxe();
        if (Util::Input::IsKeyPressed(Util::Keycode::A))
            m_Miner->Move(dt, -1);
        if (Util::Input::IsKeyPressed(Util::Keycode::D))
            m_Miner->Move(dt, 1);
        break;
    case Pickaxe::State::THROWN:
        if (IsOutOfWindow(*pickaxe))
            m_Miner->ReturnPickaxe();
        for (const auto& hittable : m_HittableList)
            if (pickaxe->IsOverlay(*hittable))
            {
                if (const auto ore = std::dynamic_pointer_cast<Ore>(hittable))
                    pickaxe->SetDragOre(ore);
                m_Miner->ReturnPickaxe();
            }
        break;
    case Pickaxe::State::RETURN:
        if (pickaxe->GetPosition().y >= m_Miner->GetThrownPosition().y)
        {
            if (const auto ore = pickaxe->TakeDragOre())
            {
                m_Money += ore->GetMoney();
                m_MoneyText->SetText(std::to_string(m_Money));
                RemoveChild(ore);
                m_HittableList.remove(ore);
            }
            m_Miner->StopPickaxe();
        }
        break;
    }
}

void GameMenu::Close()
{
    printf("[~] Close GameMenu\n");
    auto children = GetChildren();
    for (const auto& child : children)
        RemoveChild(child);
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
        if (std::any_of(m_HittableList.begin(), m_HittableList.end(), [&](const auto& other)
        {
            return other->IsOverlay(*ore);
        }))
            continue;

        AddChild(ore);
        m_HittableList.push_back(ore);
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
