#include "level.h"

Level::Level(int number, int sceneWidth, float groundLevel, int playerLives, QString backgroundPath, int sceneHeight, int startOffset, int endOffset) {
    this->number = number;
    this->sceneWidth = sceneWidth;
    this->groundLevel = groundLevel;
    this->playerLives = playerLives;
    this->backgroundPath = backgroundPath;
    this->sceneHeight = sceneHeight;
    this->startOffset = startOffset;
    this->endOffset = endOffset;
}

// Getters
int Level::getNumber() { return number; }
int Level::getSceneWidth() { return sceneWidth; }
int Level::getSceneHeight() { return sceneHeight; }
float Level::getGroundLevel() { return groundLevel * sceneHeight; }
int Level::getPlayerLives() { return playerLives; }
int Level::getStartOffset() {
    qDebug() << "I am here in level::getStartOffset";
    qDebug() << "I can see that the start offset is: " + QString::number(startOffset);
    return startOffset;
}
int Level::getEndOffset() { return endOffset; }
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

