#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "spritesheet.h"
#include "settingsmanager.h"
#include "utils.h"


extern SettingsManager SM;

class Enemy : public SpriteSheet
{

    QVector<QPixmap> spriteSheetImages;

public:
    Enemy(qreal x , qreal y , qreal scale);
    ~Enemy();


    void loadSpriteSheetImages();
};

#endif // ENEMY_H
