#include "enemy.h"
#include "settingsmanager.h"
#include "utils.h"
#include "game.h"
#include <QTimer>

// TODO : Fix flipping  bug
// TODO : Fix running in the wrong direction bug [ after flipping ]

extern SettingsManager SM;
extern Game *game;

Enemy::Enemy(qreal x, qreal y, qreal scale) {

    // Load the sprite sheet images
    loadSpriteSheetImages();

    // Set the properties of the sprite sheet
    setProperties(
            SM.settings->value("enemy/spriteFrameWidth").toInt(),
            SM.settings->value("enemy/spriteFrameHeight").toInt(),
            SM.settings->value("enemy/spriteContentOffsetX").toInt(),
            SM.settings->value("enemy/spriteContentOffsetY").toInt(),
            SM.settings->value("enemy/spriteContentWidth").toInt(),
            SM.settings->value("enemy/spriteContentHeight").toInt()
    );

    changeState(ENEMY_IDLE);
    setPos(x, y);
    setScale(scale);

    setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);

    qDebug() << "Enemy Created" << x << y << scale;

    // Check the player every 100 ms
    checkPlayerTimer = new QTimer(this);
    connect(checkPlayerTimer, &QTimer::timeout, this, &Enemy::checkPlayer);
    checkPlayerTimer->start(checkPlayerInterval);
}

void Enemy::changeDirection(PlayerDirections newDirection) {
    // If the Enemy is already facing the new direction, do nothing
    if (direction == newDirection)
        return;

    // Change the direction of the Enemy
    setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);
    direction = newDirection;
}

void Enemy::stopWalking() {
    if (walkTimer != nullptr) {
        walkTimer->stop();
        walkTimer->disconnect();
        walkTimer = nullptr;
    }
}

Enemy::~Enemy() {
    if (walkTimer != nullptr) {
        walkTimer->stop();
        walkTimer->disconnect();
        delete walkTimer;
    }
    if (checkPlayerTimer != nullptr) {
        checkPlayerTimer->stop();
        checkPlayerTimer->disconnect();
        delete checkPlayerTimer;
    }
}



void Enemy::changeState(EnemyActions newState) {
    if (currentState == newState)
        return;

    currentState = newState;
    setSpritePixmap(spriteSheetImages[currentState]);
}

void Enemy::loadSpriteSheetImages() {
    // Load the sprite sheet images
    QPixmap spriteSheet(SM.settings->value("enemy/spriteSheetPath").toString());
    qDebug() << "Sprite Sheet Loaded" << spriteSheet.width() << spriteSheet.height() << '\n';
    int frameHight = SM.settings->value("enemy/spriteFrameHeight").toInt();

    // Load the images
    for(int i = 0; i < ENEMY_ACTIONS.size(); i++) {
        int currentHight = SM.settings->value(QString("enemy/spriteSheet/%1/order").arg(ENEMY_ACTIONS[i])).toInt();
        int currentWidth = SM.settings->value(QString("enemy/spriteSheet/%1").arg(ENEMY_ACTIONS[i])).toInt();
        QPixmap pixmap = spriteSheet.copy(0 ,  currentHight*frameHight, currentWidth, frameHight);
        qDebug() << "Loaded Pixmap:"  << ENEMY_ACTIONS[i] <<  pixmap.width() << pixmap.height();
        if (pixmap.isNull()) {
            qDebug() << "Error: Failed to copy pixmap for action:" << ENEMY_ACTIONS[i];
        } else {
            spriteSheetImages.push_back(pixmap);
        }
    }
}

void Enemy::walkLeft() {
    setSpritePixmap(spriteSheetImages[WALK]);

    // Flip horizontally and adjust position
    changeDirection(LEFT);

    stopWalking(); // Stop walking in the other direction

    // Only create a new timer if it doesn't exist
    walkTimer = new QTimer(this);
    connect(walkTimer, &QTimer::timeout, this, [=]() {
        if (x() - walkSpeed > 0)
            setX(x() - walkSpeed);
    });
    walkTimer->start(SM.settings->value("spriteUpdateInterval").toInt());
}

void Enemy::walkRight() {
    setSpritePixmap(spriteSheetImages[WALK]);

    // Stop walking in the other direction
    changeDirection(RIGHT);

    // Only create a new timer if it doesn't exist
    walkTimer = new QTimer(this);
    connect(walkTimer, &QTimer::timeout, this, [=]() {
        if (x() + walkSpeed < game->scene->width())
            setX(x() + walkSpeed);
    });
    walkTimer->start(SM.settings->value("spriteUpdateInterval").toInt());
}

void Enemy::checkPlayer() {
//    // Check if the player is in the range of the enemy 50 pixels to fight the player
    if ( qAbs(x() - game->player->x()) <= fightRange) {
        stopWalking();
        fight();
        return;
    }

    // Check if the player is in the range of the enemy 400 pixels
    // If the player is in the range, start running towards the player
    if (qAbs(x() - game->player->x()) <= walkRange) {
        if (x() < game->player->x()){
            walkRight();
        }
        else if ( x() > game->player->x()){
            walkLeft();
        }
        else {
            stopWalking();
        }
    } else {  // Player is not in the range
        stopWalking();
        changeState(ENEMY_IDLE);
    }
}

void Enemy::fight() {
    changeState(ENEMY_FIGHT);

    // Flip the enemy to face the player
    if (x() < game->player->x()) {
        changeDirection(RIGHT);
    } else if ( x() < game->player->x() ) {
        changeDirection(LEFT);
    }
    // game->player->applyDamage(); TODO
}

void Enemy::die() {
    setSpritePixmap(spriteSheetImages[DIE], oneTime);
    // Time to advance frame * number of frames in the sprite sheet
    // is the time needed to play the animation
    int time = SM.settings->value("spriteUpdateInterval").toInt();
    int frameCount = SM.settings->value("enemy/spriteSheet/die").toInt() / SM.settings->value("enemy/spriteFrameWidth").toInt();
    QTimer::singleShot(time * frameCount, this, &Enemy::deleteLater);
}

void Enemy::beaten(){
    stopWalking(); // Stop walking
    setSpritePixmap(spriteSheetImages[ENEMY_BEATEN], oneTime);
}