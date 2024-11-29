#include "coin.h"
#include "game.h"
#include <QString>


extern Game *game;


QStringList Coin::soundPaths = QStringList({
    SM.settings->value("audio/coinPickUp/1").toString(),
    SM.settings->value("audio/coinPickUp/2").toString(),
    SM.settings->value("audio/coinPickUp/3").toString()
});

qreal Coin::volume = SM.settings->value("audio/coin_volume").toReal();

Coin::Coin( qreal x , qreal y , qreal scale , qreal value, QString spriteSheetPath)
{
    // Set the image
    setProperties(20, 20, 2, 1, 19, 19);
    setSpritePixmap(QPixmap(spriteSheetPath));
    animateSprite(repeating);
    // Set the position
    setPos(x , y);
    // Set the scale
    setScale(scale);
    // Set the value
    this->value = value;
    // Set the sound
    setRandomSound();
    // Check collision every 16 ms
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Coin::handleCollision);  // Correct connection
    timer->start(16);  // Check collisions every 16ms (60 FPS)

}

Coin::~Coin()
{
    // Delete the coin
    coinSound->deleteLater();
}

void Coin::setRandomSound()
{
    // Set the sound
    int mx = soundPaths.size() - 1;
    this->coinSound = new Sound(soundPaths[RandomNumber(0 ,mx)], volume , QMediaPlayer::Loops::Once);
}

void Coin::handleCollision()
{
    // if the player collides with the coin
    for ( auto &i :  collidingItems())
    {
        Player *player = dynamic_cast<Player*>(i);
        if ( player != nullptr)
        {
            // Play the sound
            coinSound->play();

            game->coinsDisplayer->increase(value);

            // Delete coin from the scene
            scene()->removeItem(this);
        }
    }
}

qreal Coin::getValue() const
{
    return value;
}
