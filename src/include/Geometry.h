#pragma once
#include <numbers>

// float x, float y
struct vector2d
{
    float x,y;
};

enum class HitSide {None, Top, Bottom, Left, Right};

HitSide circleHitRectangle(vector2d circlePosition, float circleRadius,vector2d rectanglePosition, vector2d rectangleSize);

float radians(float angle);