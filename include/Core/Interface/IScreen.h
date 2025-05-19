#ifndef I_SCREEN_H
#define I_SCREEN_H
#include "Util/Renderer.hpp"

class IScreen {
public:
    virtual ~IScreen() = default;

    virtual void Update() = 0;

    virtual void Init(Util::Renderer& m_Root) = 0;

    virtual void ShutDown(Util::Renderer& m_Root) = 0;

    void SetNextScreen(std::unique_ptr<IScreen>& nextScreen) {
        m_NextScreen = std::move(nextScreen);
    };
private:
    std::unique_ptr<IScreen> m_NextScreen;
};



#endif //I_SCREEN_H
