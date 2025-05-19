#include "Core/ScreenManager.h"


void ScreenManager::Init(Util::Renderer &root) {
    m_Root = &root;
}

void ScreenManager::NextScreen(std::unique_ptr<IScreen> screen) {
    m_NextScreen = std::move(screen);
}

void ScreenManager::UpdateScreen() {
    if (m_NextScreen) {
        if (m_CurrentScreen)
            m_CurrentScreen->ShutDown(*m_Root);
        m_CurrentScreen = std::move(m_NextScreen);
        m_CurrentScreen->Init(*m_Root);
    }
    m_CurrentScreen->Update();
}
