#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <list>

#include "Menu.h"
#include "Miner.h"
#include "Ores/Diamond.h"
#include "UI/Text.h"
#include "Util/Time.hpp"

class GameMenu final : public Menu
{
    std::shared_ptr<Miner> m_Miner;
    int m_Money = 0;
    std::list<std::shared_ptr<Ore>> m_OreList;
    std::list<std::shared_ptr<IHittable>> m_HittableList;

    std::shared_ptr<UI::Text> m_TimerText;
    std::shared_ptr<UI::Text> m_MoneyText;
    std::shared_ptr<UI::Text> m_LevelText;

public:
    GameMenu() : Menu(RESOURCE_DIR"/Background/game_background.png")
    {
    }

    void Open() override;

    void Update(App* app) override;

    void Close() override;

private:
    [[nodiscard]] static bool IsOutOfWindow(const Util::GameObject& object);
    static int RandInRange(const int min, const int max) { return rand() % (max - min + 1) + min; }
    void GenerateOre(Ore::Type type);
    void UpdateGameLogic(float dt);
};


#endif //GAMEMENU_H
