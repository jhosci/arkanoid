#pragma once
#include "Geometry.h"

class Paddle {
    //position is it's topleft corner, bottomright is in (position+size) 
    private:
        vector2d position_;
        vector2d size_;
        float velocity_;
        float minimumX_;
        float maximumX_;

    public:
        Paddle(vector2d position, vector2d size, float velocity, float minimumX, float maximumX);

        void moveRight(float dt);
        void moveLeft(float dt);

        vector2d getPosition() const;
        vector2d getSize() const;
        float getVelocity() const;
};