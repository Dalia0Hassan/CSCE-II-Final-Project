#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"
#include <QMediaPlayer>
#include <sound.h>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene* scene;
    Player * player;
    QGraphicsPixmapItem* backgroundItem;
    Game();
    ~Game();
    void centerOnPlayer();
    int lastWidth = 0, lastHeight = 0;
    Sound *bgMusicPlayer;
public slots:
    void moveWithPlayer();
    // void resizeEvent(QResizeEvent *event) override;
};

#endif // GAME_H
