#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <list>

#include "Bomb.h"
#include "Menu.h"
#include "Miner.h"
#include "UI/Text.h"
#include "Util/Time.hpp"

class GameManager
{
    std::list<std::shared_ptr<Util::GameObject>> m_HandleList;
    std::list<std::shared_ptr<Util::GameObject>> m_RemovableList;

public:
    void Update(const std::list<std::shared_ptr<IHittable>>& hittableList);

    // Getter
    std::list<std::shared_ptr<Util::GameObject>> GetRemovableList();

    // Pusher
    void PushHandle(const std::shared_ptr<Util::GameObject>& handle);
    void PushRemovable(const std::shared_ptr<Util::GameObject>& removable);

private:
    bool HandleChainExplosion(const std::shared_ptr<Bomb>& bomb,
                              const std::list<std::shared_ptr<IHittable>>& hittableList);
};


class GameMenu final : public Menu
{
    int m_Money = 0;
    std::shared_ptr<Miner> m_Miner;
    std::list<std::shared_ptr<IHittable>> m_HittableList;
    std::shared_ptr<GameManager> m_Manager = std::make_shared<GameManager>();

    std::shared_ptr<UI::Text> m_TimerText;
    std::shared_ptr<UI::Text> m_MoneyText;
    std::shared_ptr<UI::Text> m_TargetText;
    std::shared_ptr<UI::Text> m_LevelText;

    std::shared_ptr<Util::SFX> m_MoneyEffectSound;
    std::shared_ptr<Util::SFX> m_RubberRopeSound;
    std::shared_ptr<Util::SFX> m_BackgroundMusic;

public:
    GameMenu() : Menu(RESOURCE_DIR"/Background/game_background.png")
    {
        m_MoneyEffectSound = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/ring-effect.mp3");
        m_MoneyEffectSound->VolumeDown(10);
        m_RubberRopeSound = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/rubber-rope-mid.mp3");
        m_BackgroundMusic = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/background.mp3");
        m_MoneyEffectSound->VolumeDown(10);
        m_BackgroundMusic->Play(1);
    }

    void Open() override;

    void Update(App* app) override;

    void Close() override;

private:
    void UpdateGameLogic(float dt);
    void UpdatePickaxe(float dt);

    void TryPlaceObject(const std::shared_ptr<GameObject>& object);
    static int RandInRange(const int min, const int max) { return rand() % (max - min + 1) + min; }
    [[nodiscard]] static bool IsOutOfWindow(const GameObject& object);
};


#endif //GAMEMENU_H
