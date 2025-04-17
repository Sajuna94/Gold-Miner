//
// Created by ianli on 2025/3/28.
//

#ifndef IMOVEABLE_H
#define IMOVEABLE_H

class IMoveable
{
public:
    virtual ~IMoveable() = default;

    glm::vec2 GetPosition() const
    {
    }
};

#endif //IMOVEABLE_H
