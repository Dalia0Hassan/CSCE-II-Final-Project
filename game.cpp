#include "game.h"
#include "block.h"
#include "trap.h"
#include "settingsmanager.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QResizeEvent>


// TODO: use settings manager instead of hardcoding values
// SM.value("key") -> value
Game::Game() {

    setFixedSize(viewWidth, viewHeight);
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
    player->setPos(width() / 2 - player->boundingRect().height() / 2, groundLevel - player->boundingRect().height());
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

    createMap();
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

void Game::KeyPressEvent(QKeyEvent *event)
{
    // Prevent moving the view if it has focus
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left)
        return;
}


void Game::createMap() {
    // create traps in all ground
    QString path2 = SM.settings->value("spikes/1").toString();
    for ( int i = 0 ; i < 40 ; i++){
        Trap *trap = new Trap(800+ i*200, this->getGroundLevel() - 11 , path2 ,2 );
        elements.push_back(trap);
        scene->addItem(trap);
    }

    QString path3 = SM.settings->value("blocks/2").toString();

    for ( int i = 0 ; i < 20 ; i++){
        Block *block = new Block(700+ i*150, 385 ,   path3 , 1 );
        elements.push_back(block);
        scene->addItem(block);
    }

    QString path4 = SM.settings->value("blocks/3").toString();

    for ( int i = 0 ; i < 14 ; i++){
        Block *block = new Block(2800+ i*150, 300 - i*10 ,   path4 , 1);
        elements.push_back(block);
        scene->addItem(block);
    }

}
