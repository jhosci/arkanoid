#pragma once
#include "vector2d.h"

class Ball {
    private:
        vector2d position_;
        vector2d velocity_;
        float radius_;
    public:
        Ball(vector2d position, vector2d velocity, float radius);

        void updatePosition(float dt);
        void bounceX();
        void bounceY();

        vector2d getPosition() const;
        vector2d getVelocity() const;
        float getRadius() const;
    };