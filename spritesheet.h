#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QPixmap>
#include <QString>

class SpriteSheet
{
public:
    QString name;
    QPixmap pixmap;
    int frameCount;
    int frameWidth = 128;
    int frameHeight = 128;
    int spriteContentOffsetX = 45;
    int spriteContentOffsetY = 45;
    int spriteContentWidth = 30;
    int spriteContentHeight = 83;
    SpriteSheet(QString name, QString path);
};

#endif // SPRITESHEET_H
