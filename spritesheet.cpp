#include "spritesheet.h"
#include "qtimer.h"
#include "settingsmanager.h"

SpriteSheet::SpriteSheet(QString name) {
    // Initialize timer
    animationTimer = new QTimer(this);

    // Set name
    this->name = name;
}

// Logic
void SpriteSheet::setProperties(int frameWidth, int frameHeight, int xOffset, int yOffset, int contentWidth, int contentHeight) {
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->contentOffsetX = xOffset;
    this->contentOffsetY = yOffset;
    this->contentWidth = contentWidth;
    this->contentHeight = contentHeight;
}

void SpriteSheet::setSpritePixmap(QPixmap pix) {
    originalPixmap = pix;

    qDebug() << "sent:" << pix.width() << pix.height();
    qDebug() << "original:" << originalPixmap.width() << originalPixmap.height();
    qDebug() << "Porperties:" << frameWidth;

    frameCount = pix.width() / frameWidth;

    qDebug() << "Frame count:" << frameCount;

}

void SpriteSheet::animateSprite(AnimationType type) {

    currentSpriteFrame = 0;

    disconnect(animationTimer, &QTimer::timeout, this, nullptr);
    connect(animationTimer, &QTimer::timeout, this, [=](){
        advanceFrames(type);
    });

    advanceFrames(type);
    animationTimer->stop();
    animationTimer->start(SM.settings->value("spriteUpdateInterval").toInt());
}

void SpriteSheet::advanceFrames(AnimationType type) {
    // If it is a repeating action, loop the animation
    if (type == repeating)
        currentSpriteFrame = (currentSpriteFrame + 1) % frameCount;

    // If it is a one-time action, progress the animation once
    else {
        // If the animation is not done, progress
        if (currentSpriteFrame < frameCount - 1)
            currentSpriteFrame++;
    }

    // Make temp pixmap
    setPixmap(originalPixmap.copy(
            currentSpriteFrame * getFrameWidth() + getContentOffsetX(),
            getContentOffsetY(),
            getContentWidth(),
            getContentHeight()
        ));
}

// Getters
QString SpriteSheet::getName() { return name; }
int SpriteSheet::getFrameCount() { return frameCount; }
int SpriteSheet::getFrameWidth() { return frameWidth; }
int SpriteSheet::getFrameHeight() { return frameHeight; }
int SpriteSheet::getContentOffsetX() { return contentOffsetX; }
int SpriteSheet::getContentOffsetY() { return contentOffsetY; }
int SpriteSheet::getContentWidth() { return contentWidth; }
int SpriteSheet::getContentHeight() { return contentHeight; }

// Destructor
SpriteSheet::~SpriteSheet() {
    if (animationTimer != nullptr) {
        animationTimer->stop();
        delete animationTimer;
    }
}
