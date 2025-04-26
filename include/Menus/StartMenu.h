#ifndef STARTMENU_H
#define STARTMENU_H

#include "Core/Menu.h"
#include "UI/Button.h"
#include "UI/Picture.h"

class StartMenu final : public Menu
{
private:
    std::shared_ptr<UI::Button> m_StartButton;
    std::shared_ptr<UI::Picture> m_MinerPicture;

public:
    StartMenu() : Menu(RESOURCE_DIR"/Background/background.png")
    {
    }

    void Open() override;
    void Update(App* app) override;
    void Close() override;
};


#endif //STARTMENU_H
