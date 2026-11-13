#pragma once
#include "Arena.h"
#include "Ball.h"
#include "Player.h"
#include "Paddle.h"
#include "Brick.h"
#include <vector>
#include <memory> // for unique_ptr


enum class GameState {Serving, Playing, GameOver, Cleared};

class World {
    private: 
        Ball ball_; //in future might need many balls
        Arena arena_;
        Player player_;
        Paddle paddle_;

        // this is terrible
        std::vector<std::unique_ptr<Brick>> bricks_;
        GameState state_ = GameState::Serving; 

        // need std::vector<std::unique_ptr<OBJ>> for bricks (for later brick types); normal vetor can store only 1 datatype (and strips children classes from any added data)
        // it looks like I can't really avoid these damn pointers

        
        void createBallOnPaddle(); //For serving
        void handleWalls();
        void handlePaddleHit();
        void handleBrickHit();
        void removeDestroyedBricks();

    public:
        World(Ball ball, Arena arena, Player player, Paddle paddle, std::vector<std::unique_ptr<Brick>> bricks);

        void tick(float dt);

        //controls
        void movePaddleLeft(float dt);
        void movePaddleRight(float dt);
        void launchBall();

        

    };