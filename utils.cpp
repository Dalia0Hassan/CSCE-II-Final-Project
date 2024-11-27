#include "utils.h"

const QVector<QString> PLAYER_ACTIONS = {
    "idle",
    "walk",
    "run",
    "jump",
    "shield",
    "shot_1",
    "die",
    "attack_1",
    "attack_2",
    "attack_3"
};


int RandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}