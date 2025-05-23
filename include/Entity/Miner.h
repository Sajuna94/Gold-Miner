#ifndef MINER_H
#define MINER_H
#include <memory>

#include "Hook.h"
#include "UI/Picture.h"


class Miner final : public Entity {
public:
    static constexpr float kInitSpeed = 0.05f;
    static constexpr float kAccelRate = 0.0015f;
    static constexpr float kMaxSpeed = 0.3f;
    static constexpr float kDecelFactor = 0.95f;

    explicit Miner(float zIndex);

    void SetPosition(const glm::vec2 &pos) override;

    std::shared_ptr<Hook> &GetHook() { return m_Hook; }

    [[nodiscard]] bool IsMinerStopped(float epsilon = 1e-6f) const;

    void SmoothMove(int dir, float dt);

    void StopHook() const { m_Hook->Stop(); }

    void ThrowHook() const { m_Hook->Throw(); }

    void ReturnHook() {
        m_Hook->Return();
        m_Velocity = 0.0f;
    }

private:
    std::array<std::shared_ptr<UI::Picture>, 2> m_Wheels;
    std::shared_ptr<Hook> m_Hook;

    float m_Velocity = 0.0f;
};


#endif //MINER_H
