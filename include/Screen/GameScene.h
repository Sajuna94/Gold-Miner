#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include <unordered_set>

#include "Core/Interface/IScreen.h"
#include "Entity/Hook.h"
#include "Entity/Miner.h"
#include "UI/Picture.h"
#include "UI/TextBox.h"

namespace Screen {
    class GameScene final : public IScreen {
    public:
        GameScene();

        void Update() override;

        void Init(Util::Renderer &m_Root) override;

        void ShutDown(Util::Renderer &m_Root) override;

    private:
        std::shared_ptr<Util::GameObject> m_UI;

        std::shared_ptr<Miner> m_Miner;
        std::shared_ptr<Hook> m_Hook;

        std::unordered_set<std::shared_ptr<Entity>> m_Entities;

        std::shared_ptr<UI::TextBox> m_FPSTextBox;

        void MakeUI();
    };
} // Screen


#endif //GAME_SCENE_H
