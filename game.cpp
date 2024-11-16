#include "game.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QResizeEvent>
#include <QAudioOutput>

Game::Game() {


    setFixedSize(800, 600);
    // Set scene width to be 5 times the width of hte view and position it at the beginning of the view
    // Set a fixed size for the view
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QPixmap(":/Assets/images/bg_8.jpg").scaled(width(), height())));
    scene->setSceneRect(0, 0, width() * 5, height());
    setScene(scene);


    // Create and add the player object to the scene
    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(player);
    player->setPos(width() / 2 - player->boundingRect().height() / 2, height() * 0.88 - player->boundingRect().height());
    // print player position and view size
    qDebug() << player->x() << " " << player->y();
    qDebug() << width() << " " << height();
    player->setFocus();
    connect(player, &Player::playerPositionChanged, this, &Game::moveWithPlayer);
    moveWithPlayer();

    // Set scroll policies to hide scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    show();

    // Add Background Music
    bgMusicPlayer = new Sound("qrc:/Assets/audio/bg_music_1.mp3", 0.125, QMediaPlayer::Loops::Infinite);
    bgMusicPlayer->play();
}

Game::~Game() {
    delete scene;
    delete player;
    delete bgMusicPlayer;
}


void Game::moveWithPlayer() {
    // Center the view on the player with boundaries
    qreal x = qBound(viewport()->width() / 2.0, player->x(), scene->width() - viewport()->width() / 2.0);
    qreal y = qBound(viewport()->height() / 2.0, player->y(), scene->height() - viewport()->height() / 2.0);

    centerOn(x, y);
}
