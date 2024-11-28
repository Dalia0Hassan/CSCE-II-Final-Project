#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QVector>
#include <QGraphicsItem>

enum PlayerActions {
    IDLE,
    WALK,
    RUN,
    JUMP,
    SHIELD,
    DIE,
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

#endif // UTILS_H
