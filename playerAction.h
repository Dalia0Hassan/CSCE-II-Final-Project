#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <QString>
#include <QVector>

enum PlayerActions {
    IDLE,
    WALK,
    RUN,
    JUMP,
    SHIELD,
    DEAD,
    ATTACK_1,
    ATTACK_2,
    ATTACK_3
};

extern const QVector<QString> PLAYER_ACTIONS;


#endif // PLAYERACTIONS_H
