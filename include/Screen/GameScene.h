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
        std::unordered_map<std::string, int> m_Inventory;
        std::shared_ptr<Game::Logic> m_Logic;

        std::deque<float> dtQueue;
        float dtSum = 0.0f;
        std::shared_ptr<UI::TextBox> m_FPSTextBox;

        float CalculateSmoothedFPS(float dt);
    };
} // Screen


#endif //GAME_SCENE_H
