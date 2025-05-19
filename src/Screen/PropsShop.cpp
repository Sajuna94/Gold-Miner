#include "Screen/PropsShop.h"

#include "Core/ScreenManager.h"
#include "Screen/GameScene.h"
#include "UI/Picture.h"
#include "Util/Input.hpp"

namespace Screen {
    void PropsShop::Update() {
        // TAB to Game
        if (Util::Input::IsKeyDown(Util::Keycode::TAB)) {
            ScreenManager::NextScreen(std::make_unique<GameScene>());
        }
    }

    void PropsShop::Init(Util::Renderer &m_Root) {
        m_UI = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Background/shop.jpg");
        m_UI->FullScreen();
        m_UI->SetZIndex(-5);
        m_Root.AddChild(m_UI);

        const auto desk = std::make_shared<UI::Picture>(RESOURCE_DIR "/Textures/Picture/shop-desk.png");
        desk->AlignTo(UI::Picture::Align::BOTTOM);
        desk->AlignTo(UI::Picture::Align::LEFT);
        desk->SetZIndex(0);
        m_UI->AddChild(desk);
    }

    void PropsShop::ShutDown(Util::Renderer &m_Root) {
        m_Root.RemoveChild(m_UI);
    }
} // Screen
