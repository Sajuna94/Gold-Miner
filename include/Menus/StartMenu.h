#ifndef STARTMENU_H
#define STARTMENU_H

#include "Menu.h"
#include "UI/Button.h"

class StartMenu final : public Menu
{
private:
    std::shared_ptr<Button> m_StartButton;

public:
    void Open(Util::Renderer* m_Root) override;
    void Update(App* app) override;
    void Close(Util::Renderer* m_Root) const override;
};


#endif //STARTMENU_H
