#include "spritesheet.h"

SpriteSheet::SpriteSheet(QString name, QString path, int frameWidth, int frameHeight, int xOffset, int yOffset, int contentWidth, int contentHeight) {

    // Set pixmap
    pixmap = QPixmap(path);

    // Initialize values
    this->name = name;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->contentOffsetX = xOffset;
    this->contentOffsetY = yOffset;
    this->contentWidth = contentWidth;
    this->contentHeight = contentHeight;

    // Calculate number of frames
    frameCount = pixmap.width() / frameWidth;
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
