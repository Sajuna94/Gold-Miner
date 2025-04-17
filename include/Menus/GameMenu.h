#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <list>

#include "Menu.h"
#include "Miner.h"
#include "Pickaxe.h"
#include "Ores/Diamond.h"
#include "UI/Picture.h"
#include "UI/Text.h"
#include "Util/Time.hpp"

class GameMenu final : public Menu
{
    std::shared_ptr<Miner> m_Miner;
    std::shared_ptr<Pickaxe> m_Pickaxe;
    std::shared_ptr<UI::Picture> m_Rope;
    std::list<std::shared_ptr<Ore>> m_OreList;

    std::shared_ptr<UI::Text> m_TimerText;
    std::shared_ptr<UI::Text> m_MoneyText;
    std::shared_ptr<UI::Text> m_LevelText;

    std::shared_ptr<UI::Picture> m_RedLine;


public:
    int money = 0;

    explicit GameMenu(Util::Renderer* root) : Menu(root)
    {
    }

    void Open() override;

    void Update(App* app) override;

    void Close() override;

private:
    [[nodiscard]] static bool IsOutOfWindow(const Util::GameObject& object);
    static int RandInRange(const int min, const int max) { return rand() % (max - min + 1) + min; }
    void GenerateOre(Ore::Type type);
    void UpdatePickaxe(float dt);
};


#endif //GAMEMENU_H
