#ifndef LEVEL_H
#define LEVEL_H

#include "settingsmanager.h"
#include <QString>

extern SettingsManager SM;

class Level
{
private:
    int levelNumber;
    int sceneWidth;
    int sceneHeight;
    float groundLevel;
    int playerLives;
    int startOffset;
    int endOffset;
    QString backgroundPath;

public:
    Level() {};
    Level(int levelNumber, int sceneWidth, float groundLevel, int playerLives, QString backgroundPath,
        int sceneHeight = SM.settings->value("sceneDefaultHeight").toInt(),
        int startOffset = SM.settings->value("playerDefaultStartOffset").toInt(),
        int endOffset = SM.settings->value("playerDefaultEndOffset").toInt());

    // Getters
    int getLevelNumber();
    int getSceneWidth();
    int getSceneHeight();
    float getGroundLevel();
    int getStartOffset();
    int getEndOffset();
    int getPlayerLives();
    QString getBackgroundPath();
};

extern const QVector<Level> LEVELS;

#endif // LEVEL_H
