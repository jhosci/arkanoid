#pragma once
#include "vector2d.h"

class Brick {
    private:
        vector2d position_;
        vector2d size_;
        int hp_;
        
    public:
        Brick(vector2d position, vector2d size, int hp);

        void onHit();
        // bool death(); //not yet sure if it's to be done like that

        vector2d getPosition() const;
        vector2d getSize() const;
        int getHp() const;
};