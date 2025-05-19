#ifndef HOOK_H
#define HOOK_H
#include "Core/Collection.h"
#include "UI/Picture.h"

/**
 * @brief Hook class represents a hook used to throw and attach to entities.
 * It is responsible for swinging and returning, as well as hooking and releasing entities.
 */
class Hook final : public Entity {
public:
    enum class State {
        STOPPED,
        THROWN,
        RETURN,
    };

    static constexpr float kMaxSwingAngle = 80.0f;
    static constexpr float kSwingSpeed = 0.001f;
    static constexpr float kMoveSpeed = 0.3f;


    explicit Hook(float zIndex);

    [[nodiscard]] State GetState() const { return m_State; }

    [[nodiscard]] std::shared_ptr<Collection> GetHookedCollection() const;

    /**
     * @brief Checks if the hook has returned to its original position.
     * @return True if the hook has returned, otherwise false.
     */
    [[nodiscard]] bool HasReturned() const;

    void Stop();

    void Throw();

    void Return();

    void HookCollection(const std::shared_ptr<Collection> &collection);

    void ReleaseCollection();

    /**
     * @brief Advances the hook's position based on its velocity direction.
     * @param dt The time delta to apply to the movement.
     */
    void Advance(float dt);

    /**
     * @brief Swing the hook, adjusting its rotation based on the swing angle.
     * @param dt The time delta used for swinging.
     */
    void Swing(float dt);

private:
    State m_State = State::STOPPED;
    std::weak_ptr<Collection> m_HookedCollection;
    std::shared_ptr<UI::Picture> m_Rope;

    float m_SwingAngle = 0.0f;
    float m_TimeAcc = 0.0f;

    glm::vec2 m_ThrownPosition{};
    glm::vec2 m_VelocityDirection{};
};


#endif //HOOK_H
