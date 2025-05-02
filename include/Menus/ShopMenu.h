#ifndef SHOPMENU_H
#define SHOPMENU_H
#include "Core/Menu.h"
#include "Core/Product.h"
#include "UI/Button.h"

class ShopMenu final : public Menu
{
    std::vector<std::shared_ptr<Product>> m_Products;
    std::shared_ptr<UI::Button> m_NextLevelButton;

    int m_Level{};

public:
    explicit ShopMenu(const int level) : Menu(RESOURCE_DIR"/Background/game_background.png"), m_Level(level)
    {
    }

    void Open() override;
    void Update(App* app) override;
    void Close() override;

private:
    void PlaceProducts();
};


#endif //SHOPMENU_H
