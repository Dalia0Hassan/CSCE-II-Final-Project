#ifndef PLAYER_H
#define PLAYER_H

#include "playerAction.h"
#include "qpainter.h"
#include "qpen.h"
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
    float jumpVelocity = -12.0f;
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

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        // Draw the pixmap
        QGraphicsPixmapItem::paint(painter, option, widget);

        // Draw the outline
        painter->setPen(QPen(Qt::red, 3)); // Change color and thickness as needed
        painter->drawRect(boundingRect());
    }
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
    void stopJumping(int);
    void handleAttacking();
    void attack();
    void stopAttacking();
    void changeDirection(PlayerDirections);
    bool validateNewPosition(double = 0, double = 0);

    Sound * jumpSound;
    Sound * walkSound;

    void animateAction(PlayerActions, int = 0);
signals:
    void playerPositionChanged();
};

#endif // PLAYER_H
