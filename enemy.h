#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "spritesheet.h"
#include "settingsmanager.h"
#include "utils.h"


extern SettingsManager SM;

class Enemy : public SpriteSheet
{

    QVector<QPixmap> spriteSheetImages;
    QTimer *walkTimer;
    QTimer *checkPlayerTimer;
    int const walkSpeed = SM.settings->value("enemy/walkSpeed").toInt();
    int const walkRange = 400;
    int const fightRange = 50;
    int const checkPlayerInterval = 25;
    EnemyActions currentState = ENEMY_DIE;
    // TODO : change it to Direction
    PlayerDirections direction = LEFT ; // Default direction

public:
    Enemy(qreal x , qreal y , qreal scale);
    ~Enemy();

    void changeState(EnemyActions newState);
    void loadSpriteSheetImages();
    void stopWalking();
    void walkLeft();
    void walkRight();
    void checkPlayer();
    void fight();
    void die();
    void beaten();
    void changeDirection(PlayerDirections newDirection);
};

#endif // ENEMY_H
