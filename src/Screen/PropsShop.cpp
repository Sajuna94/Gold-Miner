#include "Screen/PropsShop.h"

#include "Core/LevelManager.h"
#include "Core/ScreenManager.h"
#include "Core/Math/Random.h"
#include "Screen/GameScene.h"
#include "UI/Picture.h"
#include "Util/Input.hpp"

namespace Screen {
    void PropsShop::Update() {
        if (Util::Input::IsKeyDown(Util::Keycode::TAB)) {
            LevelManager::NextLevel();
            ScreenManager::NextScreen(std::make_unique<GameScene>());
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::LCTRL) && Util::Input::IsKeyDown(Util::Keycode::R)) {
            RefreshShopItems();
        }

        m_NextLevelButton->SetImage(
            m_NextLevelButton->OnHover()
                ? RESOURCE_DIR "/Textures/Button/next-btn-hover.png"
                : RESOURCE_DIR "/Textures/Button/next-btn-normal.png"
        );
        if (m_NextLevelButton->OnClick()) {
            LevelManager::NextLevel();
            auto screen = std::make_unique<GameScene>();
            screen->SetInventory(m_Inventory);
            ScreenManager::NextScreen(std::move(screen));
        }

        bool hoverFlag = false;
        for (auto it = m_ShopButtons.begin(); it != m_ShopButtons.end();) {
            auto &btn = it->first;
            const auto &item = c_ShopItemTable.at(it->second);

            if (btn->OnHover()) {
                m_TipsTextBox->SetText(item.description);
                hoverFlag = true;
            }

            if (btn->OnClick() && m_CurrentMoney >= item.cost) {
                m_CurrentMoney -= item.cost;
                m_CurrentMoneyTextBox->SetText(std::to_string(m_CurrentMoney));
                m_Inventory[item.name]++;
                m_UI->RemoveChild(btn);
                it = m_ShopButtons.erase(it);
                continue;
            }
            ++it;
        }
        if (!hoverFlag)
            m_TipsTextBox->SetText(" ");
    }

    void PropsShop::Init(Util::Renderer &m_Root) {
        m_UI = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Background/shop.jpg");
        m_UI->FullScreen();
        m_UI->SetZIndex(-5);
        m_Root.AddChild(m_UI);

        MakeUI();
        RefreshShopItems();
    }

    void PropsShop::ShutDown(Util::Renderer &m_Root) {
        m_Root.RemoveChild(m_UI);
    }

    void PropsShop::MakeUI() {
        const auto desk = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Picture/shop-desk.png");
        desk->AlignTo(UI::Picture::Align::BOTTOM);
        desk->AlignTo(UI::Picture::Align::LEFT);
        m_UI->AddChild(desk);

        m_NextLevelButton = std::make_shared<UI::Button>(RESOURCE_DIR "/Textures/Button/next-btn-normal.png");
        m_NextLevelButton->m_Transform.scale = glm::vec2(2);
        m_NextLevelButton->m_Transform.translation = (glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT) - m_NextLevelButton->GetScaledSize()) * 0.5f + glm::vec2(-20, -25);
        m_UI->AddChild(m_NextLevelButton);

        const auto nextLevelTextBox = std::make_shared<UI::TextBox>(30, "Next Level");
        nextLevelTextBox->SetPosition(m_NextLevelButton->GetTransform().translation + glm::vec2(8, 0.0f));
        nextLevelTextBox->SetColor(Util::Color::FromName(Util::Colors::WHITE));
        m_UI->AddChild(nextLevelTextBox);

        const auto priceBg = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Picture/price-bg.png");
        priceBg->m_Transform.scale = glm::vec2(0.7f);
        priceBg->AlignTo(UI::Picture::Align::TOP_LEFT, {20, -25});
        m_UI->AddChild(priceBg);

        m_CurrentMoneyTextBox = std::make_shared<UI::TextBox>(30, std::to_string(m_CurrentMoney), UI::TextBox::Align::LEFT);
        m_CurrentMoneyTextBox->SetPosition(priceBg->GetPosition() + glm::vec2(-3, 2));
        m_CurrentMoneyTextBox->SetColor(Util::Color::FromName(Util::Colors::WHITE));
        m_UI->AddChild(m_CurrentMoneyTextBox);

        m_TipsTextBox = std::make_shared<UI::TextBox>(50, " ");
        m_TipsTextBox->m_Transform.translation = desk->m_Transform.translation + glm::vec2(0, -50);
        m_TipsTextBox->SetColor(Util::Color::FromName(Util::Colors::BROWN));
        m_UI->AddChild(m_TipsTextBox);

        for (const auto &child: m_UI->GetChildren()) {
            child->SetZIndex(10);
            if (const auto &textBox = std::dynamic_pointer_cast<UI::TextBox>(child)) {
                textBox->SetZIndex(11);
            }
        }
    }

    void PropsShop::RefreshShopItems() {
        for (const auto &[btn, name]: m_ShopButtons)
            m_UI->RemoveChild(btn);
        m_ShopButtons.clear();

        const auto level = LevelManager::CreateLevel(LevelManager::GetLevelIndex() + 1);
        std::vector<std::string> pool = {
            "StrengthDrink"
        };
        for (int i = level->GetSpawnLimits()["Rock"]; i > 0; --i)
            pool.emplace_back("Tnt");
        if (level->GetSpawnLimits()["Stone"] > 0)
            pool.emplace_back("StoneBook");
        if (level->GetSpawnLimits()["Diamond"] > 0)
            pool.emplace_back("DiamondPolish");

        constexpr size_t MaxItems = 7;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(pool.begin(), pool.end(), gen);
        const size_t count = std::min(pool.size(), MaxItems);

        float padding = 170;
        for (size_t i = 0; i < count; ++i) {
            auto item = c_ShopItemTable.at(pool[i]);

            auto btn = std::make_shared<UI::Button>(item.path);
            btn->m_Transform.translation = glm::vec2(
                -(WINDOW_WIDTH * 0.5f) + padding,
                m_TipsTextBox->m_Transform.translation.y + 200);
            btn->SetZIndex(20.0f + static_cast<float>(i));

            m_UI->AddChild(btn);
            m_ShopButtons[btn] = item.name;

            padding += btn->GetScaledSize().x + 20;
        }
    }
} // Screen
