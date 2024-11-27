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

    // Initialize level
    level = LEVELS[state.getLevel() - 1];

    // View width and height
    setFixedSize(SM.settings->value("window/width").toInt(), SM.settings->value("window/height").toInt());

    // Scene width, height, and background
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, level.getSceneWidth(), level.getSceneHeight());

    scene->setBackgroundBrush(QBrush(QPixmap(level.getBackgroundPath()).scaled(width(), height())));

    setScene(scene);


    // Player
    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);

    // Player and Scene
    scene->addItem(player);
    player->setFocus();

    // Player coordinates

    player->setPos(getStartOffset(), getGroundLevel() - player->boundingRect().height());


    // Connect player position change signal to move with player
    connect(player, &Player::playerPositionChanged, this, &Game::moveWithPlayer);
    moveWithPlayer();

    qDebug() << player->x() << " " << player->y();

    // Set scroll policies to hide scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Show the view
    show();

    // Create obstacles
    createMap();


    // Add Background Music
    bgMusicPlayer = new Sound(SM.settings->value("audio/bg/music").toString(), 0.125, QMediaPlayer::Loops::Infinite);
    bgMusicPlayer->play();

}

Game::~Game() {
    delete scene;
    delete player;
    delete bgMusicPlayer;
}

float Game::getGroundLevel() {
    return level.getGroundLevel();
}

int Game::getStartOffset() {
    return level.getStartOffset();
}

int Game::getEndOffset() {
    return level.getEndOffset();
}

int Game::getSceneWidth() {
    return level.getSceneWidth();
}

int Game::getSceneHeight() {
    return level.getSceneHeight();
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


// TODO: Position them according to ground level
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
