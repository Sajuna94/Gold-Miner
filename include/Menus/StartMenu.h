#ifndef STARTMENU_H
#define STARTMENU_H

#include "Menu.h"
#include "UI/Button.h"

class StartMenu final : public Menu {
private:
    std::shared_ptr<Button> m_StartButton;

public:
    explicit StartMenu(const Util::Renderer &root) : Menu(root) {
    }

    void Open() override;

    void Update(App *app) override;

    void Close() override;
};


#endif //STARTMENU_H
