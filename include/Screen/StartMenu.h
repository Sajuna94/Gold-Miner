#ifndef START_MENU_H
#define START_MENU_H
#include <memory>

#include "Core/Interface/IScreen.h"
#include "UI/Button.h"

namespace Screen {
    class StartMenu final : public IScreen {
    public:
        void Update() override;

        void Init(Util::Renderer &m_Root) override;

        void ShutDown(Util::Renderer &m_Root) override;

    private:
        std::shared_ptr<UI::Button> m_StartButton;
    };
} // Screen


#endif //START_MENU_H
