//should probably speedrun a C++ programming course first

struct vector2d
{
    float x,y;
};

class Ball {
    private:
        //should use var_ for class variables?
        vector2d coordinates;
        vector2d velocity;
        float radius;
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
        vector2d size;
    public:
        Wall(vector2d bottomRight);
        
        vector2d getSize() const;
};

