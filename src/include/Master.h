#pragma once
#include "Arena.h"
#include "Ball.h"
#include "Player.h"
#include "Paddle.h"
#include "Brick.h"

enum class GameState {Serving, Playing, GameOver};

class Master {
    private: 
        Ball ball_; //in future might need many balls
        Arena arena_;
        Player player_;
        Paddle paddle_;
        Brick brick_; //to read: std::vector URGENT
        GameState state_ = GameState::Serving; 


    public:
        Master(Ball ball, Arena arena, Player player, Paddle paddle, Brick brick);

        void tick(float dt);
        void handleWalls();
        void handlePaddleHit();
        void handleBrickHit();
        void removeDestroyedBricks();
        

    };