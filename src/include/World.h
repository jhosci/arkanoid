#pragma once
#include "Arena.h"
#include "Ball.h"
#include "Player.h"
#include "Paddle.h"
#include "Brick.h"
#include "LevelBuilder.h"
#include <vector>
#include <memory>

// State machine
enum class GameState {Serving, Playing, GameOver, Cleared};

class World {
    private: 
        Ball ball_; //in future might need many balls
        Arena arena_;
        Player player_;
        Paddle paddle_;
        std::vector<std::unique_ptr<Brick>> bricks_;
        GameState state_; 
        Player startingPlayer_; // used to reset the game
        
        void beginLevel();
        // put a ball on the paddle, for serving
        void createBallOnPaddle(); 
        void handleWalls();
        void handlePaddleHit();
        void handleBrickHit();
        // call std removing method of vector for bricks that have isDestroyed true
        void removeDestroyedBricks();
    public:
        World(Ball ball, Arena arena, Player player, Paddle paddle, std::vector<std::unique_ptr<Brick>> bricks,
        GameState state = GameState::Serving);

        // core behavior

        void restart();
        void startNextLevel();
        // tick is the main game loop (under graphics, just core)
        void tick(float dt);
    
        // controls

        void movePaddleLeft(float dt);
        void movePaddleRight(float dt);
        void launchBall();

        // getters for graphics layer to draw

        const Ball& ball() const { return ball_; }
        const Paddle& paddle() const { return paddle_; }
        const Player& player() const { return player_; }
        const std::vector<std::unique_ptr<Brick>>& bricks() const { return bricks_; }
        GameState state() const { return state_; }

    };