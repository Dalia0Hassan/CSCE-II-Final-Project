#include "game.h"
#include "block.h"
#include "trap.h"
#include "settingsmanager.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QResizeEvent>


Game::Game() {

    // Initialize game
    init();

}


// Logic
void Game::init() {


    // Initialize state and level
    state = new State();

    // Initialize Scene
    scene = new QGraphicsScene();
    setScene(scene);

    // View width and height
    setFixedSize(SM.settings->value("window/width").toInt(), SM.settings->value("window/height").toInt());

    // Ensuring view can receive focus
    setFocusPolicy(Qt::StrongFocus);

    // Initialize Player
    player = new Player();
    scene->addItem(player);
    connect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);

    // Background music
    bgMusicPlayer = new Sound(SM.settings->value("audio/bg/music").toString(), 0.125, QMediaPlayer::Loops::Infinite);

    // Victory sound
    victorySound = new Sound(SM.settings->value("audio/victorySound").toString());
    levelWinSound = new Sound(SM.settings->value("audio/levelWinSound").toString());

    // End flag
    endFlag = new QGraphicsPixmapItem(QPixmap(SM.settings->value("scene/endFlag").toString()).scaled(75, 115));
    scene->addItem(endFlag);

    // Coins displayer
    coinsDisplayer = new CoinsDisplay();
    coinsDisplayer->setPos(
        SM.settings->value("window/coinsDisplayerXOffset").toInt(),
        SM.settings->value("window/coinsDisplayerYOffset").toInt()
        );
    scene->addItem(coinsDisplayer);

    // Increase coins by 1 every 1 second
    QTimer * coinTimer = new QTimer(this);
    connect(coinTimer, &QTimer::timeout, coinsDisplayer, &CoinsDisplay::increment);
    coinTimer->start(1000);

}


void Game::startCurrentLevel() {

    // Initialize level
    if (level != nullptr)
        delete level;

    level = new Level(LEVELS[state->getLevel() - 1]);

    // Scene width, height, and background
    scene->setSceneRect(0, 0, level->getSceneWidth(), level->getSceneHeight());
    scene->setBackgroundBrush(QBrush(QPixmap(level->getBackgroundPath()).scaled(width(), height())));

    // Player and Scene
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->startLevel();

    // Move with player
    // Disconnect from the playerPositionChanged signal and connect again
    disconnect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);
    connect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);
    moveWithPlayer();

    // Set scroll policies to hide scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create obstacles
    createMap();

    // Play Background Music
    bgMusicPlayer->play();

    // End flag position
    endFlag->setPos(scene->width() - getEndOffset(), getGroundLevel() - endFlag->boundingRect().height());

}


void Game::handleNewLevel() {

    // Stop player movement
    player->clearFocus();
    player->setFlag(QGraphicsItem::ItemIsFocusable, false);

    // Give Player IDLE state
    player->deactivate();

    // Stop the background music
    bgMusicPlayer->stop();

    // Play the win sound
    levelWinSound->play();

    // play "victory" sound after 500 ms
    QTimer::singleShot(1000, [=](){
        victorySound->play();
        if (state->getLevel() != LEVELS.size()) {
            state->setLevel(state->getLevel() + 1);
            startCurrentLevel();
        } else
            state->setIsGameOver(true);
    });

}

// Slots
void Game::handlePlayerMovement() {

    if (player->x() >= scene->width() - getEndOffset() - player->boundingRect().width()) {
        // Handle the transition to a new level
        handleNewLevel();
        // Disconnect player position change signal
        disconnect(player, &Player::playerPositionChanged, this, &Game::handlePlayerMovement);
        return;
    }

    // Move view with the player
    moveWithPlayer();

    // Move displayers with the player
    mapDisplayersToScene();
}

void Game::KeyPressEvent(QKeyEvent *event)
{
    // Prevent moving the view if it has focus
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left) {
        event->accept();
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

// Helpers
void Game::moveWithPlayer() {

    // Center the view on the player with boundaries
    qreal x = qBound(viewport()->width() / 2.0, player->x(), scene->width() - viewport()->width() / 2.0);
    centerOn(x, viewport()->height() / 2.0);

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

void Game::mapDisplayersToScene() {
    QPointF topLeft = mapToScene(
        SM.settings->value("window/coinsDisplayerXOffset").toInt(),
        SM.settings->value("window/coinsDisplayerYOffset").toInt()
        );
    coinsDisplayer->setPos(topLeft.x(), topLeft.y());
}


// Getters
float Game::getGroundLevel() {
    return level->getGroundLevel();
}

int Game::getStartOffset() {
    return level->getStartOffset();
}

int Game::getEndOffset() {
    return level->getEndOffset();
}

int Game::getSceneWidth() {
    return level->getSceneWidth();
}

int Game::getSceneHeight() {
    return level->getSceneHeight();
}

// Destructor
Game::~Game() {
    delete scene;
    delete player;
    delete bgMusicPlayer;
    delete victorySound;
    delete levelWinSound;
    delete state;
    delete endFlag;
}
