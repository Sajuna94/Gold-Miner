#include "Screen/StartMenu.h"


namespace Screen {
    void StartMenu::Update() {
        m_StartButton->SetImage(
            m_StartButton->OnHover()
                ? RESOURCE_DIR "/Textures/Button/start-button-hover.png"
                : RESOURCE_DIR "/Textures/Button/start-button-normal.png"
        );
        // if (m_StartButton->OnClick()) {
        // }
    }

    void StartMenu::Init(Util::Renderer &m_Root) {
        m_StartButton = std::make_shared<UI::Button>(RESOURCE_DIR "/Textures/Button/start-button-normal.png");
        m_Root.AddChildren({m_StartButton});
    }

    void StartMenu::ShutDown(Util::Renderer &m_Root) {
    }
} // Screen
