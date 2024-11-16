#ifndef PLAYER_H
#define PLAYER_H

#include "playerAction.h"
#include "spritesheet.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <sound.h>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int sceneOffset = 100;
    QSet<int> keysPressed;
    QSet<PlayerActions> currentActions;
    PlayerActions dominantAction = IDLE;
    PlayerDirections direction = RIGHT;
    float jumpVelocity = -10.0f;
    float gravity = 0.5f;
    float verticalVelocity = 0.0f;
    QVector<SpriteSheet> spriteSheets;
    int currentSpriteFrame;

    QTimer *spriteTimer;
    QTimer *jumpTimer;
    QTimer * horizontalMovementTimer;
public:
    Player();

    public slots:
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void handleHorizontalMovement();

private:
    void setCurrentSprite();
    void updateSpriteFrame();
    void handleWalking();
    void handleJumping(bool);
    void updateJump(bool);
    void handleAttack();
    void changeDirection(PlayerDirections);
    bool checkSceneBoundries(int = 0);

    Sound * jumpSound;
    Sound * walkSound;

    void animateAction(PlayerActions, int = 0);
signals:
    void playerPositionChanged();
    void stopWalking();
};

#endif // PLAYER_H
