#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QVector>
#include <QGraphicsItem>
#include <random>

enum PlayerActions {
    IDLE,
    WALK,
    RUN,
    JUMP,
    SHIELD,
    SHOT_1,
    DIE,
    ATTACK_1,
    ATTACK_2,
    ATTACK_3
};

enum PlayerDirections {
    LEFT = -1,
    RIGHT = 1
};

enum CustomTypes {
    BlockType = QGraphicsItem::UserType + 1,
    TrapType,
    ShieldType,
    CoinType,
    PowerUpType
};

extern const QVector<QString> PLAYER_ACTIONS;

int RandomNumber(int min, int max) ;
#endif // UTILS_H
