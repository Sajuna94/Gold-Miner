#ifndef I_SCREEN_H
#define I_SCREEN_H
#include "Util/Renderer.hpp"

class IScreen {
public:
    virtual ~IScreen() = default;

    virtual void Update() = 0;

    virtual void Init(Util::Renderer &m_Root) = 0;

    virtual void ShutDown(Util::Renderer &m_Root) = 0;
};


#endif //I_SCREEN_H
