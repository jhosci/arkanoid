#pragma once
#include "vector2d.h"

class Ball;

/*coordinates are calculated from topleft (0,0) to bottomright (size_.x, size_.y)*/
class Arena {
    private:
        vector2d size_;
    public:
        Arena(vector2d size);
        
        //todo: split hitWallY to 2 functions for top and bottom (top=bounce, bottom=die)
        //to read passing objects to functions (references)
        bool ballHitWallX(Ball ball) const;
        bool ballHitWallY(Ball ball) const;

        //todo: limit left/right paddle movement
        //to read std::clamp()

        vector2d getSize() const;
};