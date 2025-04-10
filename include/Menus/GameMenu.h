#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Menu.h"
#include "Miner.h"
#include "Ores/Diamond.h"

class GameMenu final : public Menu {
public:
    explicit GameMenu(Util::Renderer *root) : Menu(root) {
    }

    void Open() override;

    void Update(App *app) override;

    void Close() override;

private:
    std::shared_ptr<Miner> m_Miner;
    std::vector<std::shared_ptr<Ore>> m_OreList;
};


#endif //GAMEMENU_H
