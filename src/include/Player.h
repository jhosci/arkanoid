#pragma once

// Player clas, holding lives, score, and level(now without much use)
// Methods related to manipulation of fields
class Player {
    private:
        int lives_;
        int score_;
        int level_;
    public:
        Player(int lives=3, int score=0, int level=1);


        void nextLevel();
        void raiseScore(int delta);
        void loseLife();
        
        bool gameOver() const;
        int getLives() const;
        int getScore() const;
        int getLevel() const;
};