#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Menu.h"
#include "Miner.h"

class GameMenu final : public Menu
{
private:
    std::shared_ptr<Miner> m_Miner;
public:
    explicit GameMenu(Util::Renderer &root) : Menu(root) {
    }
    void Open() override;
    void Update(App* app) override;
    void Close() override;
};


#endif //GAMEMENU_H
