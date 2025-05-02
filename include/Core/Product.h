#ifndef PRODUCT_H
#define PRODUCT_H
#include <memory>

#include "Interfaces/IClickable.h"
#include "UI/Picture.h"
#include "UI/Text.h"


class Product final : public IClickable
{
    const int m_Cost;
    std::shared_ptr<Util::Image> m_Image;
    std::shared_ptr<UI::Text> m_Text;

    bool m_WaitingMouseUp = false;

public:
    std::shared_ptr<UI::Picture> m_Picture;
    std::shared_ptr<UI::Text> m_DescriptionText;

    Product(const int cost, const std::string& imagePath, const std::string& description)
        : m_Cost(cost),
          m_Picture(std::make_shared<UI::Picture>(imagePath, 5)),
          m_DescriptionText(std::make_unique<UI::Text>(description, 30))
    {
    }

    bool IsClicked() override;
    bool OnHover() const override;

    [[nodiscard]] int GetCost() const;
};


#endif //PRODUCT_H
