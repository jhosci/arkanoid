#pragma once
#include "Geometry.h"

class Brick {
    private:
        vector2d position_;
        vector2d size_;
        int hp_;
        
    public:
        Brick(vector2d position, vector2d size, int hp);


        // to read: virtual functions to delete children classes w/o memory leaks URGENT
        void onHit();
        bool isDestroyed() const;


        vector2d getPosition() const;
        vector2d getSize() const;
        int getHp() const;
};