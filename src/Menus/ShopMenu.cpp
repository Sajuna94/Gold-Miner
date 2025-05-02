#include "Menus/ShopMenu.h"

#include "Core/GameConfig.h"

namespace
{
    using ProductFactory = std::function<std::shared_ptr<Product>()>;

    const std::unordered_map<Item::Props, ProductFactory> kProductFactories = {
        {
            Item::Props::TNT,
            []()
            {
                return std::make_shared<Product>(
                    150, GetPath(Item::Props::TNT),
                    "R鍵垂直丟出TNT炸毀岩石層");
            }
        },
        {
            Item::Props::STONE_LIGHT,
            []()
            {
                return std::make_shared<Product>(
                    500, GetPath(Item::Props::STONE_LIGHT),
                    "讓下一局的石頭變得輕盈");
            }
        },
    };
}


void ShopMenu::Open()
{
    m_NextLevelButton = std::make_shared<UI::Button>("", 1);
}

void ShopMenu::Update(App* app)
{
    std::vector<Item::Props> m_BuyedItems;
    for (const auto& product : m_Products)
    {
        // if (product->IsClicked())
            // m_BuyedItems.push_back()

    }
}

void ShopMenu::Close()
{
}

void ShopMenu::PlaceProducts()
{
    for (const auto& product : m_Products)
    {
    }
}
