#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "shieldeffect.h"
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
    float jumpVelocity = -10.75f;
    float gravity = 0.375f;
    float verticalVelocity = 0.0f;
    QVector<SpriteSheet> spriteSheets;
    int currentSpriteFrame;
    bool isWalking = false;
    bool isRunning = false;
    bool isJumping = false;
    bool isFalling = false;
    bool isAttacking = false;
    bool isDying = false;
    bool hasShield = false;

    QTimer *spriteTimer = nullptr;
    QTimer *jumpTimer = nullptr;
    QTimer *fallTimer = nullptr;
    QTimer *walkTimer = nullptr;
    QTimer *attackTimer = nullptr;
    QTimer *collisionTimer = nullptr;

    ShieldEffect * shield = nullptr;
public:
    Player();
    ~Player();

    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
    //     // Draw the pixmap
    //     QGraphicsPixmapItem::paint(painter, option, widget);

    //     // Draw the outline
    //     painter->setPen(QPen(Qt::red, 3)); // Change color and thickness as needed
    //     painter->drawRect(boundingRect());
    // }
    public slots:
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void focusOutEvent(QFocusEvent * event) override;



private:
    void setCurrentSprite();
    void updateSpriteFrame();
    void handleWalking();
    void walk();
    void stopWalking();
    void handleJumping();
    void jump(int = 0);
    void stopJumping();
    void handleFalling(int = 0);
    void fall(int = 0);
    void stopFalling();
    void handleAttacking();
    void attack();
    void stopAttacking();
    void handleDying();
    void die();
    void stopDying();
    void handleCollision();
    void handleCoinCollision(QGraphicsItem*);
    void handleShieldCollision(QGraphicsItem*);
    void handlePowerUpCollision(QGraphicsItem*);
    void handleDangerCollision(QGraphicsItem*);

    void changeDirection(PlayerDirections);
    QGraphicsItem* validateNewPosition(double = 0, double = 0);
    double findBestY(double, double, double);
    void enableShield();
    void disableShield();
    void hide();
    void show();
    void start();

    Sound * jumpSound;
    Sound * walkSound;
    Sound * dieSound;
    Sound * destroySound;
    Sound * shieldActiviationSound;
    Sound * wooHooSound;
    Sound * coinSound;

    void animateAction(PlayerActions, int = 0);
signals:
    void playerPositionChanged();
};

#endif // PLAYER_H
