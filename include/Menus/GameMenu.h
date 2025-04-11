#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Menu.h"
#include "Miner.h"
#include "Pickaxe.h"
#include "Ores/Diamond.h"
#include "UI/Text.h"
#include "Util/Time.hpp"

class GameMenu final : public Menu {
public:
    explicit GameMenu(Util::Renderer *root) : Menu(root) {
    }

    void Open() override;

    void Update(App *app) override;

    void Close() override;

private:
    std::shared_ptr<Miner> m_Miner;
    std::shared_ptr<Pickaxe> m_Pickaxe;
    std::vector<std::shared_ptr<Ore>> m_OreList;

    std::shared_ptr<UI::Text> m_TimerText;
};


#endif //GAMEMENU_H
