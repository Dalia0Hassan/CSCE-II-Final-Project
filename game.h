#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "level.h"
#include "player.h"
#include <QMediaPlayer>
#include "sound.h"
#include "state.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    QVector<QGraphicsPixmapItem*> elements;
    State state;
    Level level;
    Sound *bgMusicPlayer;
public:
    // TODO: Make them private and modify that everywhere
    QGraphicsScene* scene;
    Player * player;
    QGraphicsPixmapItem* backgroundItem;

public:
    Game();
    ~Game();

    // Getters
    float getGroundLevel();
    int getPlayerStartOffset();
    int getPlayerEndOffset();
    int getSceneWidth();
    int getSceneHeight();


private:
    // Helpers
    void centerOnPlayer();
    void createMap();
public slots:
    void moveWithPlayer();
    void KeyPressEvent(QKeyEvent *event);
};

#endif // GAME_H
