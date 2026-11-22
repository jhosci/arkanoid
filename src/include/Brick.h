#pragma once
#include "Geometry.h"

// Brick class manages it's position, size, health and score
// uses virtual onHit and destroyer, to enable later implementation of brick subclasses (eg. powerup brick, invulnerable brick etc.)
class Brick {
    private:
        vector2d position_;
        vector2d size_;
        int hp_;
        int score_;
        
    public:
        Brick(vector2d position, vector2d size, int hp, int score=10);

        // destructor has to be virtual if method has >=1 virtual methods (if not, destroying a child obj will not free the additional data the child overwritten, causing memleaks)
        virtual ~Brick() = default;
        
        virtual void onHit(HitSide side = HitSide::None);
        bool isDestroyed() const;

        vector2d getPosition() const;
        vector2d getSize() const;
        int getHp() const;
        int getScore() const;
};


class ArmoredBrick:public Brick {
    private:
        HitSide armoredSide_;

    public:
        ArmoredBrick(vector2d position, vector2d size, int hp, HitSide armoredSide, int score = 10);

        void onHit(HitSide side = HitSide::None) override;
};