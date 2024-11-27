#include "level.h"

Level::Level(int levelNumber, int sceneWidth, float groundLevel, int playerLives, QString backgroundPath, int sceneHeight, int playerStartOffset, int playerEndOffset) {
    this->levelNumber = levelNumber;
    this->sceneWidth = sceneWidth;
    this->groundLevel = groundLevel;
    this->playerLives = playerLives;
    this->backgroundPath = backgroundPath;
    this->sceneHeight = sceneHeight;
    this->playerStartOffset = playerStartOffset;
    this->playerEndOffset = playerEndOffset;
}

// Getters
int Level::getLevelNumber() { return levelNumber; }
int Level::getSceneWidth() { return sceneWidth; }
int Level::getSceneHeight() { return sceneHeight; }
float Level::getGroundLevel() { return groundLevel * sceneHeight; }
int Level::getPlayerLives() { return playerLives; }
int Level::getPlayerStartOffset() { return playerStartOffset; }
int Level::getPlayerEndOffset() { return playerEndOffset; }
QString Level::getBackgroundPath() { return backgroundPath; }

// Initialize levels
const QVector<Level> LEVELS = {
    Level(
        1,
        SM.settings->value("levels/1/sceneWidth").toInt(),
        SM.settings->value("levels/1/groundLevel").toFloat(),
        SM.settings->value("levels/1/playerLives").toInt(),
        SM.settings->value("levels/1/backgroundPath").toString()),
    Level(
        2,
        SM.settings->value("levels/2/sceneWidth").toInt(),
        SM.settings->value("levels/2/groundLevel").toFloat(),
        SM.settings->value("levels/2/playerLives").toInt(),
        SM.settings->value("levels/2/backgroundPath").toString()),
    Level(
        3,
        SM.settings->value("levels/3/sceneWidth").toInt(),
        SM.settings->value("levels/3/groundLevel").toFloat(),
        SM.settings->value("levels/3/playerLives").toInt(),
        SM.settings->value("levels/3/backgroundPath").toString()),
    Level(
        4,
        SM.settings->value("levels/4/sceneWidth").toInt(),
        SM.settings->value("levels/4/groundLevel").toFloat(),
        SM.settings->value("levels/4/playerLives").toInt(),
        SM.settings->value("levels/4/backgroundPath").toString()),
    Level(
        5,
        SM.settings->value("levels/5/sceneWidth").toInt(),
        SM.settings->value("levels/5/groundLevel").toFloat(),
        SM.settings->value("levels/5/playerLives").toInt(),
        SM.settings->value("levels/5/backgroundPath").toString())
};

