#ifndef PROPS_SHOP_H
#define PROPS_SHOP_H
#include "Core/Interface/IScreen.h"
#include "UI/Button.h"
#include "UI/Picture.h"
#include "UI/TextBox.h"
#include "Util/SFX.hpp"

namespace Screen {
    class PropsShop final : public IScreen {
    public:
        void Update() override;

        void Init(Util::Renderer &m_Root) override;

        void ShutDown(Util::Renderer &m_Root) override;

        void SetMoney(const int money) { m_CurrentMoney = money; }

    private:
        struct ShopItem {
            int cost;
            std::string name;
            std::string description;
            std::string path;
        };

        struct ProductObject {
            std::shared_ptr<UI::Button> imgBtn;
            std::shared_ptr<UI::TextBox> costTb;
            std::string name;
        };

        const std::unordered_map<std::string, ShopItem> c_ShopItemTable = {
            {
                "Tnt", {
                    500, "Tnt",
                    "Press Q to throw straight down. Destroys rocks.",
                    RESOURCE_DIR "/Textures/tnt.png"
                }
            },
            {
                "StoneBook", {
                    700, "StoneBook",
                    "Makes stones lighter.",
                    RESOURCE_DIR "/Textures/stone-collectors-book.png"
                }
            },
            {
                "StrengthDrink", {
                    1500, "StrengthDrink",
                    "Increases hook power.",
                    RESOURCE_DIR "/Textures/strength-drink.png"
                }
            },
            {
                "DiamondPolish", {
                    1000, "DiamondPolish",
                    "Diamonds sell for more.",
                    RESOURCE_DIR "/Textures/diamond-polish.png"
                }
            },
        };

        int m_CurrentMoney{};
        std::vector<ProductObject> m_Products;
        std::unordered_map<std::string, int> m_Inventory;

        std::shared_ptr<UI::Picture> m_UI;

        std::shared_ptr<UI::TextBox> m_CurrentMoneyTextBox;
        std::shared_ptr<UI::Button> m_NextLevelButton;
        std::shared_ptr<UI::TextBox> m_TipsTextBox;

        std::shared_ptr<Util::SFX> m_CashSound;

        void MakeUI();

        void RefreshShopItems();
    };
} // Screen

#endif //PROPS_SHOP_H
