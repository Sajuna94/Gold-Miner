#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <list>

#include "Core/Menu.h"
#include "GamePlay/GameLogic.h"
#include "UI/Text.h"
#include "Util/SFX.hpp"
#include "Util/Time.hpp"

class GameMenu final : public Menu
{
    std::shared_ptr<GameLogic> m_GameLogic;

    std::shared_ptr<UI::Text> m_FPSText;

    std::shared_ptr<UI::Text> m_MoneyText;
    std::shared_ptr<UI::Text> m_TargetText;
    std::shared_ptr<UI::Text> m_TimeLeftText;
    std::shared_ptr<UI::Text> m_LevelText;

    std::shared_ptr<Util::SFX> m_MoneyEffectSound;
    std::shared_ptr<Util::SFX> m_RubberRopeSound;
    // std::shared_ptr<Util::SFX> m_BackgroundMusic;

    std::unordered_set<std::shared_ptr<std::pair<float, std::shared_ptr<UI::Text>>>> m_TextAnimeBuffer;

public:
    GameMenu() : Menu(RESOURCE_DIR"/Background/game_background.png")
    {
        const auto time = Util::Time::GetElapsedTimeMs();
        printf("Loading mp3 file\n");
        m_MoneyEffectSound = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/ring-effect.mp3");
        // m_MoneyEffectSound->VolumeDown(10);
        m_RubberRopeSound = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/rubber-rope-mid.mp3");
        // m_BackgroundMusic = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/background.mp3");
        // m_MoneyEffectSound->VolumeDown(10);
        // m_BackgroundMusic->Play(1);
        printf("Loading finish %f ms\n", Util::Time::GetElapsedTimeMs() - time);
    }

    void Open() override;

    void Update(App* app) override;

    void Close() override;

private:
    void HandleCommand(GameLogic::CommandType command);

    void AnimeAddedMoney(float dt);
};


#endif //GAMEMENU_H
