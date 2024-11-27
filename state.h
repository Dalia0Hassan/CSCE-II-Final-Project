#ifndef STATE_H
#define STATE_H

class State
{
private:
    int coins = 0;
    int lives = 5;
    int level = 1;
    bool isGameOver = false;
    bool isPaused = false;
public:
    State();

    // Getters
    int getCoins();
    int getLives();
    int getLevel();
    bool getIsGameOver();
    bool getIsPaused();

    // Setters
    void setCoins(int coins);
    void setLives(int lives);
    void setLevel(int level);
    void setIsGameOver(bool isGameOver);
    void setIsPaused(bool isPaused);
};

#endif // STATE_H
