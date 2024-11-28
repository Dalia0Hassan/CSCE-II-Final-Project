#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "qgraphicsitem.h"
#include "utils.h"
#include <QPixmap>
#include <QString>

class SpriteSheet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
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

    // Original pixmap
    QPixmap originalPixmap;

    // Animation
    QTimer *animationTimer = nullptr;
    int currentSpriteFrame = 0;

public:

public:
    SpriteSheet(QString name = "");
    ~SpriteSheet();

    // Logic
    void setProperties(int frameWidth, int frameHeight, int xOffset, int yOffset, int contentWidth, int contentHeight);
    void setSpritePixmap(QPixmap pixmap);
    void animateSprite(AnimationType = repeating);

    // Getters
    QString getName();
    int getFrameCount();
    int getFrameWidth();
    int getFrameHeight();
    int getContentOffsetX();
    int getContentOffsetY();
    int getContentWidth();
    int getContentHeight();


private:
    // Helper
    void advanceFrames(AnimationType);

};

#endif // SPRITESHEET_H
