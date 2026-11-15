#pragma once
#include "Geometry.h"

class Brick {
    private:
        vector2d position_;
        vector2d size_;
        int hp_;
        int score_;
        
    public:
        Brick(vector2d position, vector2d size, int hp, int score=10);

        virtual ~Brick() = default;
        
        virtual void onHit();
        bool isDestroyed() const;

        vector2d getPosition() const;
        vector2d getSize() const;
        int getHp() const;
        int getScore() const;
};