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
    bgMusicPlayer = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    audioOutput->setVolume(0.125);
    bgMusicPlayer->setAudioOutput(audioOutput);
    bgMusicPlayer->setSource(QUrl("qrc:/Assets/audio/bg_music_1.mp3"));
    bgMusicPlayer->play();


    connect(bgMusicPlayer, &QMediaPlayer::playbackStateChanged, [this](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            this->bgMusicPlayer->play();
        }
    });
}

Game::~Game() {
    delete scene;
    delete player;
    delete bgMusicPlayer;
}
// void Game::resizeEvent(QResizeEvent *event) {
//     // Calculate the ratio in width and height change
//     double ratioWidth = (double)event->size().width() / lastWidth;
//     double ratioHeight = (double)event->size().height() / lastHeight;
//     scene->setSceneRect(0, 0, scene->width() * ratioWidth, event->size().height());
//     scene->setBackgroundBrush(QBrush(QPixmap(":/Assets/images/bg_8.jpg").scaled(width(), height())));

//     lastWidth = width();
//     lastHeight = height();
//     QGraphicsView::resizeEvent(event);
// }



void Game::moveWithPlayer() {
    // Center the view on the player with boundaries
    qreal x = qBound(viewport()->width() / 2.0, player->x(), scene->width() - viewport()->width() / 2.0);
    qreal y = qBound(viewport()->height() / 2.0, player->y(), scene->height() - viewport()->height() / 2.0);

    centerOn(x, y);
}
