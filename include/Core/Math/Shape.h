#ifndef SHAPE_H
#define SHAPE_H
#include <glm/vec2.hpp>

struct rect {
    glm::vec2 center;
    glm::vec2 size;

    explicit rect()
        : center(0, 0), size(0, 0) {
    }

    explicit rect(const glm::vec2 size)
        : center(0, 0), size(size) {
    }

    explicit rect(const glm::vec2 center, const glm::vec2 size)
        : center(center), size(size) {
    }

    /**
     * @brief Checks whether a point is inside the rectangle.
     *
     * @param point The point to test.
     * @return true if point is within the rect, false otherwise.
     */
    [[nodiscard]] bool contains(const glm::vec2 &point) const {
        const float halfWidth = size.x * 0.5f;
        const float halfHeight = size.y * 0.5f;

        return std::abs(point.x - center.x) <= halfWidth &&
               std::abs(point.y - center.y) <= halfHeight;
    }

    /**
     * @brief Checks whether this rectangle intersects with another rectangle.
     *
     * @param other The other rectangle.
     * @return true if rectangles intersect, false otherwise.
     */
    [[nodiscard]] bool intersect(const rect &other) const {
        const float halfWidthA = size.x * 0.5f;
        const float halfHeightA = size.y * 0.5f;
        const float halfWidthB = other.size.x * 0.5f;
        const float halfHeightB = other.size.y * 0.5f;

        return std::abs(center.x - other.center.x) <= (halfWidthA + halfWidthB) &&
               std::abs(center.y - other.center.y) <= (halfHeightA + halfHeightB);
    }
};

namespace hit {
    inline bool intersect(const rect &rectA, const rect &rectB) {
        // check the X-axis range
        if (rectA.center.x + rectA.size.x * 0.5f < rectB.center.x - rectB.size.x * 0.5f ||
            rectA.center.x - rectA.size.x * 0.5f > rectB.center.x + rectB.size.x * 0.5f) {
            return false;
        }
        // check the Y-axis range
        if (rectA.center.y + rectA.size.y * 0.5f < rectB.center.y - rectB.size.y * 0.5f ||
            rectA.center.y - rectA.size.y * 0.5f > rectB.center.y + rectB.size.y * 0.5f) {
            return false;
        }
        return true;
    }
}

#endif //SHAPE_H
