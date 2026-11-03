#pragma once
//should probably speedrun a C++ programming course first

//every non-circular position is it's topleft corner coordinates (so )

struct vector2d
{
    float x,y;
};

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

class Arena {
    private:
        vector2d size_;
    public:
        Arena(vector2d size);
        
        //todo: split hitWallY to 2 functions for top and bottom (top=bounce, bottom=die)
        bool ballHitWallX(Ball ball) const;
        bool ballHitWallY(Ball ball) const;

        //todo: limit left/right paddle movement
        //to read std::clamp()

        vector2d getSize() const;
};

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

class Paddle {
    //position is it's topleft corner, bottomright is in (position+size) 
    private:
        vector2d position_;
        vector2d size_;
        float velocity_;

    public:
        Paddle(vector2d position, vector2d size, float velocity);

        void moveRight(float dt);
        void moveLeft(float dt);

        vector2d getPosition() const;
        vector2d getSize() const;
        float getVelocity() const;
};