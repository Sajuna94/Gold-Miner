#include "Menus/GameMenu.h"
#include "App.hpp"
#include "Util/Input.hpp"
#include <iostream>

#include "Bomb.h"
#include "Ores/Diamond.h"
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


    std::list<std::shared_ptr<GameObject>> presetObjects;

    for (int i = 0; i < 20; ++i) presetObjects.push_back(std::make_shared<Gold>());
    for (int i = 0; i < 5; ++i) presetObjects.push_back(std::make_shared<Rock>());
    for (int i = 0; i < 5; ++i) presetObjects.push_back(std::make_shared<Bomb>());
    for (int i = 0; i < 10; ++i) presetObjects.push_back(std::make_shared<Diamond>());

    presetObjects.sort([](const auto& a, const auto& b)
    {
        auto aSize = a->GetScaledSize();
        auto bSize = b->GetScaledSize();
        return aSize.x * aSize.y > bSize.x * bSize.y;
    });
    for (const auto& obj : presetObjects)
        TryPlaceObject(obj);
    presetObjects.clear();


    printf("WINDOW_SIZE: %d, %d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameMenu::Update(App* app)
{
    const float dt = Util::Time::GetDeltaTimeMs() / 1000.0f;
    m_TimerText->SetText("FPS: " + std::to_string(1.0f / dt));

    UpdateGameLogic(dt);
}

void GameMenu::UpdateGameLogic(const float dt)
{
    m_Miner->Update(dt);
    UpdatePickaxe(dt);

    m_Manager->Update(m_HittableList);
    for (const auto& removable : m_Manager->GetRemovableList())
    {
        if (const auto hittable = std::dynamic_pointer_cast<IHittable>(removable))
            m_HittableList.remove(hittable);
        RemoveChild(removable);
    }
}

void GameMenu::Close()
{
    printf("[~] Close GameMenu\n");
    auto children = GetChildren();
    for (const auto& child : children)
        RemoveChild(child);
}

void GameMenu::TryPlaceObject(const std::shared_ptr<GameObject>& object)
{
    const auto moveable = std::dynamic_pointer_cast<IMoveable>(object);
    const auto hittable = std::dynamic_pointer_cast<IHittable>(object);

    int tryingCount = 0;
    while (tryingCount < 20)
    {
        tryingCount++;

        moveable->SetPosition({
            RandInRange(-HALF_WINDOW_WIDTH, HALF_WINDOW_WIDTH),
            RandInRange(-HALF_WINDOW_HEIGHT, HALF_WINDOW_HEIGHT - 250)
        });

        if (IsOutOfWindow(*object))
            continue;
        if (std::any_of(m_HittableList.begin(), m_HittableList.end(),
                        [&](const auto& other) { return other->IsOverlay(*hittable); }))
            continue;

        AddChild(object);
        m_HittableList.push_back(hittable);
        break;
    }
}

void GameMenu::UpdatePickaxe(float dt)
{
    switch (const auto pickaxe = m_Miner->GetPickaxe(); pickaxe->GetState())
    {
    case Pickaxe::State::STOP:
        if (!Util::Input::IsKeyPressed(Util::Keycode::SPACE))
            pickaxe->UpdateAngle(dt);
        if (Util::Input::IsKeyPressed(Util::Keycode::A))
            m_Miner->Move(dt, -1);
        if (Util::Input::IsKeyPressed(Util::Keycode::D))
            m_Miner->Move(dt, 1);
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB))
            m_Miner->ThrowPickaxe();
        break;
    case Pickaxe::State::THROWN:
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB))
            m_Miner->ReturnPickaxe();
        if (IsOutOfWindow(*pickaxe))
            m_Miner->ReturnPickaxe();
        for (const auto& hittable : m_HittableList)
            if (pickaxe->IsOverlay(*hittable))
            {
                if (const auto ore = std::dynamic_pointer_cast<Ore>(hittable))
                    pickaxe->SetDragOre(ore);
                else if (const auto bomb = std::dynamic_pointer_cast<Bomb>(hittable))
                {
                    bomb->Explosion();
                    m_Manager->PushHandle(bomb);
                }
                m_Miner->ReturnPickaxe();
                break;
            }
        break;
    case Pickaxe::State::RETURN:
        if (pickaxe->GetPosition().y >= m_Miner->GetThrownPosition().y)
        {
            if (const auto ore = pickaxe->TakeDragOre())
            {
                m_Money += ore->GetMoney();
                m_Manager->PushRemovable(ore);
                m_MoneyText->SetText(std::to_string(m_Money));
                m_MoneyEffectSound->Play();
            }
            m_Miner->StopPickaxe();
        }
        break;
    }
}


bool GameMenu::IsOutOfWindow(const GameObject& object)
{
    const glm::vec2 centerPt = object.GetTransform().translation;
    const glm::vec2 halfEdgeSize = (glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) - object.GetScaledSize()) * 0.5f;
    return
        any(lessThan(centerPt, -halfEdgeSize)) ||
        any(greaterThan(centerPt, halfEdgeSize));
}

void GameManager::Update(const std::list<std::shared_ptr<IHittable>>& hittableList)
{
    const auto temp = m_HandleList;
    for (const auto& handle : temp)
    {
        if (const auto bomb = std::dynamic_pointer_cast<Bomb>(handle))
            if (HandleChainExplosion(bomb, hittableList))
                m_HandleList.remove(bomb);
    }
}

bool GameManager::HandleChainExplosion(const std::shared_ptr<Bomb>& bomb,
                                       const std::list<std::shared_ptr<IHittable>>& hittableList)
{
    if (!bomb->IsBlownUp())
        return false;

    PushRemovable(bomb);
    for (const auto& hittable : hittableList)
    {
        if (bomb->InTheBlowRange(hittable))
        {
            if (const auto otherBomb = std::dynamic_pointer_cast<Bomb>(hittable))
            {
                if (otherBomb->IsBlownUp())
                    continue;
                otherBomb->Explosion();
                PushHandle(otherBomb);
            }
            else
                PushRemovable(std::dynamic_pointer_cast<Util::GameObject>(hittable));
        }
    }
    return true;
}


void GameManager::PushHandle(const std::shared_ptr<Util::GameObject>& handle)
{
    m_HandleList.push_back(handle);
}

void GameManager::PushRemovable(const std::shared_ptr<Util::GameObject>& removable)
{
    m_RemovableList.push_back(removable);
}

std::list<std::shared_ptr<Util::GameObject>> GameManager::GetRemovableList()
{
    return m_RemovableList;
}
