#ifndef STATE_H
#define STATE_H

#include "qobject.h"

class State : public QObject
{
    Q_OBJECT
private:
    int coins;
    int lives;
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
    void incrementCoins();
    void decrementLives();
    void increamentLives();

    // Signals
signals:
    void stateChanged();
};

#endif // STATE_H
