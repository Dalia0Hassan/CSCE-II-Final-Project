#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"
#include <QMediaPlayer>
#include "sound.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    QVector<QGraphicsPixmapItem*> elements;
public:
    const int viewWidth = 800, viewHeight = 600;
    const int playerStartOffset = 100, playerEndOffset = 100;
    const float groundLevel = 0.88 * viewHeight;
    QGraphicsScene* scene;
    Player * player;
    QGraphicsPixmapItem* backgroundItem;
    Game();
    ~Game();
    void centerOnPlayer();
    int lastWidth = 0, lastHeight = 0;
    Sound *bgMusicPlayer;
    float getGroundLevel() { return groundLevel; }
    void createMap();
public slots:
    void moveWithPlayer();
    void KeyPressEvent(QKeyEvent *event);
};

#endif // GAME_H
