#include "enemy.h"
#include "settingsmanager.h"
#include "utils.h"


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

    setSpritePixmap(spriteSheetImages[IDLE]);
    setPos(x, y);
    setScale(scale);
    qDebug() << "Enemy Created" << x << y << scale;
}

Enemy::~Enemy() {

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


