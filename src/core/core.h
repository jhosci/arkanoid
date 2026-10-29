//should probably speedrun a C++ programming course first

struct vector2d
{
    float x,y;
};

class Ball {
    private:
        vector2d coordinates_;
        vector2d velocity_;
        float radius_;
    public:
        Ball(vector2d startPos, vector2d startVel, float ballRadius);

        void update_pos();
        void bounceX();
        void bounceY();

        vector2d getPos() const;
        vector2d getVel() const;
    };

class Wall {
    private:
        vector2d size_;
    public:
        Wall(vector2d bottomRight);
        
        vector2d getSize() const;
};

class Brick {
    private:
        vector2d coordinates_;
        int hp_;
    public:
        Brick(vector2d coordinates, int hp);

        vector2d getPos() const;
        int getHp() const;
};