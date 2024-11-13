#include "spritesheet.h"

SpriteSheet::SpriteSheet(QString name, QString path) {
    this->name = name;
    pixmap = QPixmap(path);
    frameWidth = 128;
    frameHeight = pixmap.height();
    frameCount = pixmap.width() / 128;
    frameDuration = 100;
}
