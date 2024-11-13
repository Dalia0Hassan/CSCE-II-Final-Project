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
    int frameDuration;
    int frameWidth = 128;
    int frameHeight = 128;
    SpriteSheet(QString name, QString path);
};

#endif // SPRITESHEET_H
