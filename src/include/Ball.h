#pragma once
#include "Geometry.h"

// Ball class manages things related to ball (pos, vel, radius) and methods of bouncing and moving
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
        void setVelocity(vector2d newVelocity);

        vector2d getPosition() const;
        vector2d getVelocity() const;
        float getRadius() const;
    };