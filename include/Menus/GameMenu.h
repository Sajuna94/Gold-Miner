#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Menu.h"
#include "Miner.h"

class GameMenu final : public Menu
{
private:
    std::shared_ptr<Miner> m_Miner;
public:
    void Open(Util::Renderer* m_Root) override;
    void Update(App* app) override;
    void Close(Util::Renderer* m_Root) const override;
};


#endif //GAMEMENU_H
