#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <deque>

#include "Core/Interface/IScreen.h"
#include "Game/Logic.h"
#include "UI/TextBox.h"

namespace Screen {
    class GameScene final : public IScreen {
    public:

        void Update() override;

        void Init(Util::Renderer &m_Root) override;

        void ShutDown(Util::Renderer &m_Root) override;

        void SetInventory(std::unordered_map<std::string, int> inventory) { m_Inventory = std::move(inventory); }

    private:
        void MakeUI();

        std::shared_ptr<Util::GameObject> m_UI;

        std::shared_ptr<Game::Logic> m_Logic;
        std::unordered_map<std::string, int> m_Inventory;

        int m_ElapsedTime = 0;
        int m_ElapsedMoney = 0;
        std::shared_ptr<UI::TextBox> m_MoneyTextBox;
        std::shared_ptr<UI::TextBox> m_GoalTextBox;
        std::shared_ptr<UI::TextBox> m_LevelTextBox;
        std::shared_ptr<UI::TextBox> m_TimeTextBox;

        std::deque<float> dtQueue;
        float dtSum = 0.0f;
        std::shared_ptr<UI::TextBox> m_FpsTextBox;

        std::shared_ptr<Util::SFX> m_MoneySound;

        void RefreshLevel(int levelIndex);

        float CalculateSmoothedFPS(float dt);

        static void ToPropsShop(int money);
    };
} // Screen


#endif //GAME_SCENE_H
