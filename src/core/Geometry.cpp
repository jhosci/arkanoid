#include "Geometry.h"
#include <cmath>
#include <algorithm>
#include <numbers>

HitSide circleHitRectangle(vector2d circlePosition, float circleRadius,vector2d rectanglePosition, vector2d rectangleSize) {
    float closestX = std::clamp(circlePosition.x, rectanglePosition.x, rectanglePosition.x + rectangleSize.x);
    float closestY = std::clamp(circlePosition.y, rectanglePosition.y, rectanglePosition.y + rectangleSize.y);

    float dx = circlePosition.x - closestX;
    float dy = circlePosition.y - closestY;

    if (dx * dx + dy * dy > circleRadius * circleRadius) return HitSide::None;

    if (std::abs(dx) > std::abs(dy)) {
        if (dx > 0) return HitSide::Right;
        else return HitSide::Left;
    } else {
        if (dy < 0) return HitSide::Top;
        else return HitSide::Bottom;
    }
}

float radians(float angle) {return angle * std::numbers::pi / 180.0f;}
