#pragma once
#include "Geometry.h"

class Ball;

enum class WallContact {None, SideWall, Ceiling, Floor};

/*coordinates are calculated from topleft (0,0) to bottomright (size_.x, size_.y)*/
class Arena {
    private:
        vector2d size_;

    public:
        Arena(vector2d size);

        WallContact checkWallHit(Ball &ball) const;

        vector2d getSize() const;
};