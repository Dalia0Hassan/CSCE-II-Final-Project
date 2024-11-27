#include "state.h"

State::State() {}

// Getters
int State::getCoins() { return coins; }
int State::getLives() { return lives; }
int State::getLevel() { return level; }
bool State::getIsGameOver() { return isGameOver; }
bool State::getIsPaused() { return isPaused; }

// Setters
void State::setCoins(int coins) { this->coins = coins; }
void State::setLives(int lives) { this->lives = lives; }
void State::setLevel(int level) { this->level = level; }
void State::setIsGameOver(bool isGameOver) { this->isGameOver = isGameOver; }
void State::setIsPaused(bool isPaused) { this->isPaused = isPaused; }
