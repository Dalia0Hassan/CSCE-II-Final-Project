#ifndef PLAYER_H
#define PLAYER_H

#include "playerAction.h"
#include "spritesheet.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include "sound.h"
#include <QKeyEvent>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    const int sceneOffset = 100, walkShift = 3, runShift = 5;
    QSet<int> keysPressed;
    QSet<PlayerActions> currentActions;
    PlayerActions dominantAction = IDLE;
    PlayerDirections direction = RIGHT;
    float jumpVelocity = -10.0f;
    float gravity = 0.5f;
    float verticalVelocity = 0.0f;
    QVector<SpriteSheet> spriteSheets;
    int currentSpriteFrame;
    bool isJumping = false;
    bool isAttacking = false;

    QTimer *spriteTimer;
    QTimer *jumpTimer;
    QTimer *walkTimer;
    QTimer *attackTimer;
public:
    Player();
    ~Player();

    public slots:
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void focusOutEvent(QFocusEvent * event);

private:
    void setCurrentSprite();
    void updateSpriteFrame();
    void handleWalking();
    void walk();
    void stopWalking();
    void handleJumping();
    void jump(int = 0);
    void stopJumping(int);
    void handleAttacking();
    void attack();
    void stopAttacking();
    void changeDirection(PlayerDirections);
    bool checkSceneBoundries(int = 0);

    Sound * jumpSound;
    Sound * walkSound;

    void animateAction(PlayerActions, int = 0);
signals:
    void playerPositionChanged();
};

#endif // PLAYER_H
