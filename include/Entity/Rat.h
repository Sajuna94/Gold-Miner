#ifndef RAT_H
#define RAT_H
#include "Collection.h"


class Rat final : public Collection {
public:
    explicit Rat();

    void Update(float dt);

private:
    bool m_IsMoving = false;
    float m_NextMovementMs;
    float m_Boundary;
    int m_CurrentDir{};

    [[nodiscard]] int GetRandomTick() const;

    void SetDir(int dir);

    void HandleMovementAnmi() const;
};


#endif //RAT_H
