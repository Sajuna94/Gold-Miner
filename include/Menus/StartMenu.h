#ifndef STARTMENU_H
#define STARTMENU_H

#include "Menu.h"
#include "UI/Button.h"

class StartMenu final : public Menu {
public:
    explicit StartMenu(Util::Renderer *root) : Menu(root) {
    }

    void Open() override;

    void Update(App *app) override;

    void Close() override;

private:
    std::shared_ptr<UI::Button> m_StartButton;
};


#endif //STARTMENU_H
