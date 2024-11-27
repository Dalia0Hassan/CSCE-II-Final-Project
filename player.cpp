#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "game.h"
#include <QTime>

extern Game *game;

Player::Player() {

    // Loading audio files
    jumpSound = new Sound("qrc:/Assets/audio/man_jumps_1.wav");
    walkSound = new Sound("qrc:/Assets/audio/man_walks.wav", 1, QMediaPlayer::Infinite);
    dieSound = new Sound("qrc:/Assets/audio/male_death_sound.mp3");
    shieldActiviationSound = new Sound("qrc:/Assets/audio/shield_active.mp3");
    coinSound = new Sound("qrc:/Assets/audio/coin_pickup.mp3");
    destroySound = new Sound("qrc:/Assets/audio/shield_hit.m4a");
    wooHooSound = new Sound("qrc:/Assets/audio/woo_hoo.mp3");



    // Loading sprite sheets
    for(int i = 0; i < PLAYER_ACTIONS.size(); i++) {
        QString filename = PLAYER_ACTIONS[i];
        filename[0] = filename[0].toUpper();
        QString path = QString(":/Assets/images/Fighter/%1.png").arg(filename);
        spriteSheets.push_back(SpriteSheet(PLAYER_ACTIONS[i], path));
    }

    // Walk timer
    walkTimer = new QTimer(this);
    connect(walkTimer, &QTimer::timeout, this, &Player::walk);

    // Jump timer
    jumpTimer = new QTimer(this);
    fallTimer = new QTimer(this);

    // Sprite timer
    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Player::updateSpriteFrame);
    spriteTimer->start(75); // Update every 75ms

    // Collision Timer
    collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &Player::handleCollision);
    collisionTimer->start(16);


    updateSpriteFrame();

    // enable shield after 3 seconds
    QTimer::singleShot(3000, this, &Player::enableShield);

    // Remove it after 5 seconds
    QTimer::singleShot(5000, this, &Player::disableShield);

}

void Player::keyPressEvent(QKeyEvent *event) {

    // Avoid auto repeat key press
    if (event->isAutoRepeat())
        return;

    // Avoid multiple key presses
    if (keysPressed.contains(event->key()))
        return;

    // Add the key to the pressed keys set
    keysPressed.insert(event->key());

    // Handle the key press
    if (event->key() == Qt::Key_A)
        handleAttacking();
    else if (event->key() == Qt::Key_Shift)
        isRunning = true;
    else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        // Handle walking
        handleWalking();
    else if (event->key() == Qt::Key_Space)
        // Handle the jump
        handleJumping();

    // Update the sprite sheet
    setCurrentSprite();
}

void Player::keyReleaseEvent(QKeyEvent *event) {

    // Avoid auto repeat key release
    if (event->isAutoRepeat())
        return;

    // Avoid multiple removes
    if (!keysPressed.contains(event->key()))
        return;

    // Remove the key from the pressed keys set
    keysPressed.remove(event->key());

    // Handle the key release
    if ((event->key() == Qt::Key_Left && !keysPressed.contains(Qt::Key_Right))
        || (event->key() == Qt::Key_Right && !keysPressed.contains(Qt::Key_Left)))
        stopWalking();
    else if (event->key() == Qt::Key_Shift)
        isRunning = false;

    // Update the sprite sheet
    setCurrentSprite();
}
void Player::setCurrentSprite() {
    PlayerActions newDominantAction;
    if (isDying)
        newDominantAction = DIE;
    else if (isAttacking)
        newDominantAction = ATTACK_1;
    else if (isJumping)
        newDominantAction = JUMP;
    else if (isWalking)
        newDominantAction = isRunning ? RUN : WALK;
    else
        newDominantAction = IDLE;

    if (newDominantAction != dominantAction)
        currentSpriteFrame = 0;

    dominantAction = newDominantAction;
}

void Player::updateSpriteFrame() {

    // If it is a repeating action, loop the animation
    if (dominantAction == PlayerActions::WALK || dominantAction == PlayerActions::RUN || dominantAction == PlayerActions::IDLE)
        currentSpriteFrame = (currentSpriteFrame + 1) % spriteSheets[dominantAction].frameCount;

    // If it is a one-time action, progress the animation once
    else if (dominantAction == PlayerActions::JUMP || dominantAction == PlayerActions::ATTACK_1 || dominantAction == PlayerActions::DIE) {
        // If the animation is not done, progress
        if (currentSpriteFrame < spriteSheets[dominantAction].frameCount - 1)
            currentSpriteFrame++;
        // If it is done, remove the action
        // else
        //     currentActions.remove(dominantAction);
    }

    // Set the new sprite frame
    setPixmap(
        spriteSheets[dominantAction].pixmap.copy(
            currentSpriteFrame * spriteSheets[dominantAction].frameWidth + spriteSheets[dominantAction].spriteContentOffsetX,
            spriteSheets[dominantAction].spriteContentOffsetY,
            spriteSheets[dominantAction].spriteContentWidth,
            spriteSheets[dominantAction].spriteContentHeight
            )
        );
}

void Player::handleWalking() {

    isWalking = true;
    // Play Walking sound
    walkSound->play();
    // Start timer to handle horizontal movement
    walkTimer->start(16);
}

void Player::stopWalking() {
    // Stop walking sound
    walkSound->stop();
    // Stop the horizontal movement timer
    walkTimer->stop();
    // Remove the walking action
    // currentActions.remove(WALK);
    isWalking = false;
    // Update the sprite sheet
    setCurrentSprite();
}

void Player::walk() {

    // Do not move if the player is jumping
    if (isJumping || isAttacking || isDying) {
        stopWalking();
        return;
    }

    // Shift amount for walking and running
    int shift = isRunning ? 5 : 3;
    if (!isJumping && !isFalling && qAbs(game->getGroundLevel() - boundingRect().height() - y()) > 2 && (validateNewPosition(0, 3) == nullptr || validateNewPosition(5, 3) == nullptr || validateNewPosition(-5, 3) == nullptr)) {
        handleFalling((shift - 2) * direction);
        stopWalking();
        return;
    }

    // If the player wants to walk to the left
    if (keysPressed.contains(Qt::Key_Left)) {
        // Make the displacement in negative direction
        shift *= -1;

        // Change the direction of the player if needed
        changeDirection(LEFT);
    } else if (keysPressed.contains(Qt::Key_Right))
        changeDirection(RIGHT);

    // Move the player if it is within the scene boundaries
    QGraphicsItem *collidingItem = validateNewPosition(shift, 0);
    if (collidingItem == nullptr || collidingItem->type() == TrapType) {
        setPos(x() + shift, y());
        emit playerPositionChanged();
    } else if (collidingItem->type() == BlockType) {
        setPos(x() + findBestY(shift, 0, 0), y());
        emit playerPositionChanged();
        stopWalking();
    }
}

void Player::focusOutEvent(QFocusEvent *event) {
    // Give the focus back to the player
    Q_UNUSED(event);
    setFocus();
}

void Player::handleJumping() {
    // Do not jump if the player is already jumping
    if (isJumping)
        return;

    // Change state
    isJumping = true;
    // Play jump sound
    jumpSound->play();
    // Set the initial vertical velocity
    verticalVelocity = jumpVelocity;
    // Disconnect timer and start it again
    jumpTimer->disconnect();

    if (keysPressed.contains(Qt::Key_Left))
        changeDirection(LEFT);
    else if (keysPressed.contains(Qt::Key_Right))
        changeDirection(RIGHT);

    int xShift = 0;
    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
        xShift = direction * (isRunning ? runShift : walkShift);
    jumpTimer->connect(jumpTimer, &QTimer::timeout, this, [=](){
        jump(xShift);
    });
    jumpTimer->start(16);
}



void Player::jump(int xShift) {
    // Update vertical position
    verticalVelocity += gravity;
    setY(y() + verticalVelocity);

    if (verticalVelocity >= 0) {
        jumpTimer->stop();
        handleFalling(xShift);
        return;
    }

    QGraphicsItem *collidingItem = validateNewPosition(xShift, verticalVelocity);
    if (collidingItem == nullptr)
        setY(y() + verticalVelocity);
    else {
        setY(y() + findBestY(xShift, verticalVelocity, 0));
        handleFalling();
        return;
    }

    collidingItem = validateNewPosition(xShift, 0);
    // Adjust the view to follow the player
    if (xShift != 0 && collidingItem == nullptr) {
        setX(x() + xShift);
        emit playerPositionChanged();
    }

    verticalVelocity += gravity;
}

void Player::stopJumping() {
    // Remove the jump action
    // currentActions.remove(JUMP);
    isJumping = false;
    isFalling = false;
    // Stop the jump timer
    jumpTimer->stop();
    // If the player was moving before jumping, continue moving
    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
        handleWalking();
    // Update the sprite sheet
    setCurrentSprite();
}

void Player::handleFalling(int xShift) {
    // Do not fall if the player is already falling
    if (isFalling)
        return;

    verticalVelocity = 0;

    // Change state
    isFalling = true;
    // Disconnect timer and start it again
    fallTimer->disconnect();
    fallTimer->connect(fallTimer, &QTimer::timeout, this, [=](){
        fall(xShift);
    });
    fallTimer->start(16);
}

void Player::fall(int xShift) {

    if (y() > game->getGroundLevel() - boundingRect().height()) {
        setY(game->getGroundLevel() - boundingRect().height());
        stopFalling();
        return;
    }

    QGraphicsItem *collidingItem = validateNewPosition(xShift, verticalVelocity);
    // Move the player by the current vertical velocity
    if (collidingItem != nullptr)
    qDebug() << TrapType << BlockType << collidingItem->type();
    if (collidingItem == nullptr || collidingItem->type() == TrapType) {
        qDebug() << "Colliding with non-blocks";
        setY(y() + verticalVelocity);
    }
    else {

        // check if the player's foot is above the block
        if (y() + boundingRect().height() - verticalVelocity <= collidingItem->y()) {
            setY(collidingItem->y() - boundingRect().height());
            stopFalling();
            return;
        } else {
            setY(y() + verticalVelocity);
        }
    }

    // Adjust the view to follow the player
    if (xShift != 0 && validateNewPosition(xShift) == nullptr) {
        setX(x() + xShift);
        emit playerPositionChanged();
    }


    verticalVelocity += gravity;
}

void Player::stopFalling() {
    // Remove the fall action
    isFalling = false;
    isJumping = false;
    // Stop the fall timer
    fallTimer->stop();

    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
        handleWalking();

    // Update the sprite sheet
    setCurrentSprite();
}

void Player::handleAttacking() {
    // Avoid conflicting attacks
    if (isAttacking)
        return;
    // Insert the attack action
    isAttacking = true;

    // One time attack
    attack();
}

void Player::attack() {
    // Play attack sound
    // attackSound->play();
    // Stop the attack after 250ms
    setCurrentSprite();
    QTimer::singleShot(375, this, &Player::stopAttacking);

}

void Player::stopAttacking() {

    // Stop attacking
    isAttacking = false;
    // currentActions.remove(ATTACK_1);

    // Restart walking timer
    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
        handleWalking();

    // Update the sprite sheet
    setCurrentSprite();

}

void Player::handleDying() {
    // Avoid conflicting dies
    if (isDying)
        return;
    isDying = true;

    // One time die
    die();
}

void Player::die() {
    // Play dying sound
    dieSound->play();
    // Stop the dying after 250ms
    setCurrentSprite();
    QTimer::singleShot(225, this, &Player::stopDying);

}

void Player::stopDying() {

    // Call the function start after 1000 second
    QTimer::singleShot(1000, this, &Player::start);

}

void Player::handleCollision() {
    for(QGraphicsItem * item : collidingItems()) {
        if (item == shield || item == this) continue;
        if (item->type() == TrapType)
            handleDangerCollision(item);
    }
}

void Player::handleDangerCollision(QGraphicsItem* item) {
    if (hasShield && item->type() == TrapType) {
        // Remove item from the scene and delete it
        game->scene->removeItem(item);
        delete item;

        // Play destroy sound
        destroySound->play();
    } else
        handleDying();
}

void Player::enableShield() {
    if (!shield) {
        shield = new ShieldEffect(this);
        game->scene->addItem(shield);
        shieldActiviationSound->play();
        wooHooSound->play();
        hasShield = true;
    }
}

void Player::disableShield() {
    if (shield) {
        game->scene->removeItem(shield);
        delete shield;
        shield = nullptr;
        hasShield = false;
    }
}

void Player::changeDirection(PlayerDirections newDirection) {
    // If the player is already facing the new direction, do nothing
    if (direction == newDirection)
        return;

    // Change the direction of the player
    setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);
    direction = newDirection;
}

QGraphicsItem* Player::validateNewPosition(double dx, double dy) {
    int newXPosition = x() + dx, newYPosition = y() + dy;
    if (newXPosition - sceneOffset < 0 || newXPosition + sceneOffset > game->scene->width() - boundingRect().width())
        return this;

    QRectF newRect(newXPosition, newYPosition, boundingRect().width(), boundingRect().height());
    QList<QGraphicsItem*> collidingItems = game->scene->items(newRect);
    for(QGraphicsItem * item : collidingItems) {
        if (item == this)
            continue;
        if (item->type() == TrapType || item->type() == BlockType)
            return item;
    }

    return nullptr;
}

double Player::findBestY(double dx, double dy, double l) {
    double r = dy;
    int loop = 30;
    while(loop--) {
        double mid = (l + r) / 2;
        if (validateNewPosition(dx, mid) == nullptr) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

void Player::hide() {
    setOpacity(0);
}

void Player::show() {
    setOpacity(1);
}

void Player::start() {

    // Hide player
    hide();


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        if (x() > game->getPlayerStartOffset()) {
            setX(x() - 15);
            emit playerPositionChanged();
        }
        else {
            setPos(game->getPlayerStartOffset(), game->getGroundLevel() - boundingRect().height());
            timer->stop();
            timer->disconnect();
            delete timer;
            show();
            isDying = false;
            setCurrentSprite();
        }
    });
    timer->start(16);

}

// Free memory
Player::~Player() {
    delete jumpSound;
    delete walkSound;
    delete dieSound;
    delete spriteTimer;
    delete jumpTimer;
    delete walkTimer;
    delete fallTimer;
    delete attackTimer;
    delete collisionTimer;
    delete shield;
}
