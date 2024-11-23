#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "game.h"
#include <QTime>
#include "block.h"
#include "trap.h"

extern Game *game;

Player::Player() {

    // Loading audio files
    jumpSound = new Sound("qrc:/Assets/audio/man_jumps_1.wav");
    walkSound = new Sound("qrc:/Assets/audio/man_walks.wav", 1, QMediaPlayer::Infinite);


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

    // Sprite timer
    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Player::updateSpriteFrame);
    spriteTimer->start(75); // Update every 100ms

    // Set the initial sprite
    updateSpriteFrame();
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
        currentActions.insert(RUN);
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
            currentActions.remove(RUN);

    // Update the sprite sheet
    setCurrentSprite();
}
void Player::setCurrentSprite() {
    PlayerActions newDominantAction;
    if (currentActions.contains(ATTACK_1))
        newDominantAction = ATTACK_1;
    else if (currentActions.contains(JUMP))
        newDominantAction = JUMP;
    else if (currentActions.contains(WALK))
        newDominantAction = currentActions.contains(RUN) ? RUN : WALK;
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
    else if (dominantAction == PlayerActions::JUMP || dominantAction == PlayerActions::ATTACK_1) {
        // If the animation is not done, progress
        if (currentSpriteFrame < spriteSheets[dominantAction].frameCount - 1)
            currentSpriteFrame++;
        // If it is done, remove the action
        else
            currentActions.remove(dominantAction);
    }

    // Set the new sprite frame
    setPixmap(
        spriteSheets[dominantAction].pixmap.copy(
            currentSpriteFrame * spriteSheets[dominantAction].frameWidth + spriteSheets[dominantAction].spriteContentOffsetX,
            spriteSheets[dominantAction].spriteContentOffsetY,
            spriteSheets[dominantAction].spriteContentWidth + (dominantAction == RUN || dominantAction == JUMP ? 10 : 0),
            spriteSheets[dominantAction].spriteContentHeight
            )
        );
}

void Player::handleWalking() {
    // Insert the walking action
    currentActions.insert(WALK);
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
    currentActions.remove(WALK);
    // Update the sprite sheet
    setCurrentSprite();
}

void Player::walk() {

    // Do not move if the player is jumping
    if (isJumping || isAttacking) {
        stopWalking();
        return;
    }

    // Shift amount for walking and running
    int shift = currentActions.contains(RUN) ? 5 : 3;

    // If the player wants to walk to the left
    if (keysPressed.contains(Qt::Key_Left)) {
        // Make the displacement in negative direction
        shift *= -1;

        // Change the direction of the player if needed
        changeDirection(LEFT);
    } else if (keysPressed.contains(Qt::Key_Right))
        changeDirection(RIGHT);

    // Move the player if it is within the scene boundaries
    if (validateNewPosition(shift)) {
        setPos(x() + shift, y());
        emit playerPositionChanged();
    } else
        stopWalking();
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
    // Insert the jump action
    currentActions.insert(JUMP);
    isJumping = true;
    // Play jump sound
    jumpSound->play();
    // Set the initial vertical velocity
    verticalVelocity = jumpVelocity;
    // Disconnect timer and start it again
    jumpTimer->disconnect();
    jumpTimer->connect(jumpTimer, &QTimer::timeout, this, [=](){
        int xShift = 0;
        if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
            xShift = direction * (currentActions.contains(RUN) ? runShift : walkShift);
        jump(xShift);
    });
    jumpTimer->start(16);
}

void Player::jump(int xShift) {
    // Update the player's vertical velocity (gravity effect)
    verticalVelocity += gravity;

    // Move the player by the current vertical velocity
    setY(y() + verticalVelocity);

    // Adjust the view to follow the player
    if (xShift != 0 && validateNewPosition(xShift)) {
        setX(x() + xShift);
        emit playerPositionChanged();
    }

    // Stop the jump when the player lands (y position >= ground level)
    if (y() >= game->getGroundLevel() - boundingRect().height())
        stopJumping(xShift);
}

void Player::stopJumping(int xShift) {
    // Reset to ground level
    setY(game->getGroundLevel() - boundingRect().height());
    // Remove the jump action
    currentActions.remove(JUMP);
    isJumping = false;
    // Stop the jump timer
    jumpTimer->stop();
    // If the player was moving before jumping, continue moving
    if (xShift != 0)
        handleWalking();
    // Update the sprite sheet
    setCurrentSprite();
}

void Player::handleAttacking() {
    // Avoid conflicting attacks
    if (isAttacking)
        return;
    // Insert the attack action
    currentActions.insert(ATTACK_1);
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
    currentActions.remove(ATTACK_1);

    // Restart walking timer
    if (keysPressed.contains(Qt::Key_Left) || keysPressed.contains(Qt::Key_Right))
        handleWalking();

    // Update the sprite sheet
    setCurrentSprite();

}

void Player::changeDirection(PlayerDirections newDirection) {
    // If the player is already facing the new direction, do nothing
    if (direction == newDirection)
        return;

    // Change the direction of the player
    setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);
    direction = newDirection;
}

bool Player::validateNewPosition(double dx, double dy) {
    int newXPosition = x() + dx, newYPosition = y() + dy;
    if (newXPosition - sceneOffset < 0 || newXPosition + sceneOffset > game->scene->width() - boundingRect().width())
        return false;

    // QRectF newRect(newXPosition, newYPosition, boundingRect().width(), boundingRect().height());
    // QList<QGraphicsItem*> collidingItems = game->scene->items(newRect);
    // for(QGraphicsItem * item : collidingItems) {
    //     if (item == this)
    //         continue;
    //     if (item->type() == Block::Type || item->type() == Trap::Type)
    //         return false;
    // }

    return true;
}

// Free memory
Player::~Player() {
    delete jumpSound;
    delete walkSound;
    delete spriteTimer;
    delete jumpTimer;
    delete walkTimer;
}
