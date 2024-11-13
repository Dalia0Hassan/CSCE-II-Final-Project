#ifndef PLAYER_H
#define PLAYER_H

#include "playerAction.h"
#include "spritesheet.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <QMediaPlayer>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QSet<int> keysPressed;
    QSet<PlayerActions> currentActions;
    PlayerActions dominantAction = IDLE;
    int direction = 1;
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
    void handleJumping(bool);
    void updateJump(bool);
    void handleAttack();

    QMediaPlayer * jumpSound;
    QMediaPlayer * walkSound;

signals:
    void playerPositionChanged();
};

#endif // PLAYER_H
