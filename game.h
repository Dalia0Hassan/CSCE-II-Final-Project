#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "coinsdisplay.h"
#include "level.h"
#include "player.h"
#include <QMediaPlayer>
#include "sound.h"
#include "state.h"
#include"livesdisplay.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:

    // Trackers
    QVector<QGraphicsPixmapItem*> elements;
    State *state = nullptr;
    Level *level = nullptr;

    // Sounds
    Sound *victorySound, *levelWinSound;
    Sound *bgMusicPlayer;


    // UI
    QGraphicsPixmapItem *endFlag;
    CoinsDisplay *coinsDisplayer;
    livesDisplay *lifedisplayer;

public:
    // TODO: Make them private and modify that everywhere
    QGraphicsScene* scene = nullptr;
    Player * player = nullptr;


public:

    // Constructor and destructor
    Game();
    ~Game();

    // Getters
    float getGroundLevel();
    int getStartOffset();
    int getEndOffset();
    int getSceneWidth();
    int getSceneHeight();

private:
    // Logic
    void init();
    void startCurrentLevel();
    void handleNewLevel();

    // Helpers
    void createMap();
    void moveWithPlayer();
    void mapDisplayersToScene();

public slots:
    // Slots
    void handlePlayerMovement();
    void KeyPressEvent(QKeyEvent *event);

    // Friends
    friend int main(int argc, char *argv[]);
};

extern Game *game;

#endif // GAME_H
