#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
#include <memory>

#include "Interface/IScreen.h"


class ScreenManager {
public:
    static void Init(Util::Renderer &root);

    static void NextScreen(std::unique_ptr<IScreen> screen);

    static void UpdateScreen();

private:
    inline static std::unique_ptr<IScreen> m_CurrentScreen = nullptr;
    inline static std::unique_ptr<IScreen> m_NextScreen = nullptr;
    inline static Util::Renderer *m_Root = nullptr;
};


#endif //SCREEN_MANAGER_H
