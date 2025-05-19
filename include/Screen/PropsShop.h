#ifndef PROPS_SHOP_H
#define PROPS_SHOP_H
#include "Core/Interface/IScreen.h"
#include "UI/Picture.h"

namespace Screen {
    class PropsShop final : public IScreen {
    public:
        void Update() override;

        void Init(Util::Renderer &m_Root) override;

        void ShutDown(Util::Renderer &m_Root) override;

    private:
        std::shared_ptr<UI::Picture> m_UI;
    };
} // Screen

#endif //PROPS_SHOP_H
