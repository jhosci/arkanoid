#pragma once
#include <numbers>

// Vector2d is a structure of a pair of floats, like sfml::vector2f
// float x, float y
struct vector2d
{
    float x,y;
};

// Need to determine how ball should bounce off
enum class HitSide {None, Top, Bottom, Left, Right};

// circleHitRectangle() returns HitSide, is pure geometry function taking only positions and sizes
HitSide circleHitRectangle(vector2d circlePosition, float circleRadius,vector2d rectanglePosition, vector2d rectangleSize);

// c++ cannot convert deg to rad on it's own
float radians(float angle);