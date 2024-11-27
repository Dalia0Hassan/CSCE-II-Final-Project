#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QPixmap>
#include <QString>

class SpriteSheet
{
private:
    // Name for sprite sheet
    QString name;


    // Number of frames in the sheet (Calculated in the constructor)
    int frameCount;

    // Width and height of each frame
    int frameWidth;
    int frameHeight;

    // Offset of the content in the sprite
    int contentOffsetX;
    int contentOffsetY;

    // Width and height of the content in the sprite
    int contentWidth;
    int contentHeight;
public:
    // Pixmap for sprite sheet
    QPixmap pixmap;

public:
    SpriteSheet(QString name, QString path, int frameWidth, int frameHeight, int xOffset, int yOffset, int contentWidth, int contentHeight);

    // Getters
    QString getName();
    int getFrameCount();
    int getFrameWidth();
    int getFrameHeight();
    int getContentOffsetX();
    int getContentOffsetY();
    int getContentWidth();
    int getContentHeight();

};

#endif // SPRITESHEET_H
