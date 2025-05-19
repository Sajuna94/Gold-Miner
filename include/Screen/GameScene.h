#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <deque>
#include <unordered_set>

#include "Core/Interface/IScreen.h"
#include "Entity/Hook.h"
#include "Entity/Miner.h"
#include "Game/Logic.h"
#include "Game/Spawner.h"
#include "UI/TextBox.h"

namespace Screen {
    class GameScene final : public IScreen {
    public:
        void Update() override;

        void Init(Util::Renderer &m_Root) override;

        void ShutDown(Util::Renderer &m_Root) override;

    private:
        void MakeUI();

        std::shared_ptr<Util::GameObject> m_UI;
        std::shared_ptr<Game::Logic> m_Logic;

        std::shared_ptr<Miner> m_Miner;
        std::shared_ptr<Hook> m_Hook;

        std::shared_ptr<Game::Spawner> m_Spawner;

        std::deque<float> dtQueue;
        float dtSum = 0.0f;
        std::shared_ptr<UI::TextBox> m_FPSTextBox;

        float CalculateSmoothedFPS(float dt);
    };
} // Screen


#endif //GAME_SCENE_H
