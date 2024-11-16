#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <game.h>
#include <QTime>

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

    // Setting up the timer
    horizontalMovementTimer = new QTimer(this);
    connect(horizontalMovementTimer, SIGNAL(timeout()), this, SLOT(handleHorizontalMovement()));

    jumpTimer = new QTimer(this);

    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Player::updateSpriteFrame);
    spriteTimer->start(75); // Update every 100ms

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
        currentActions.insert(ATTACK_3);
    else if (event->key() == Qt::Key_Shift)
        currentActions.insert(RUN);
    else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        currentActions.insert(WALK);
        handleWalking();
    }
    else if (event->key() == Qt::Key_Space) {
        currentActions.insert(JUMP);
        // Handle the jump
        handleJumping(currentActions.contains(WALK));
    }

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
    if (
        (event->key() == Qt::Key_Left && !keysPressed.contains(Qt::Key_Right))
        || (event->key() == Qt::Key_Right && !keysPressed.contains(Qt::Key_Left))
        ) {
        stopWalking();
    }
    else if (event->key() == Qt::Key_Shift)
            currentActions.remove(RUN);
    else if (event->key() == Qt::Key_A) {
        currentActions.remove(ATTACK_3);
    }

    // Update the sprite sheet
    setCurrentSprite();
}
void Player::setCurrentSprite() {
    PlayerActions newDominantAction;
    if (currentActions.contains(ATTACK_3))
        newDominantAction = ATTACK_3;
    else if (currentActions.contains(JUMP))
        newDominantAction = JUMP;
    else if (currentActions.contains(WALK))
        newDominantAction = currentActions.contains(RUN) ? RUN : WALK;
    else
        newDominantAction = IDLE;

    dominantAction = newDominantAction;
}

void Player::updateSpriteFrame() {

    // If it is a repeating action, loop the animation
    if (dominantAction == PlayerActions::WALK || dominantAction == PlayerActions::RUN || dominantAction == PlayerActions::IDLE)
        currentSpriteFrame = (currentSpriteFrame + 1) % spriteSheets[dominantAction].frameCount;

    // If it is a one-time action, progress the animation once
    else if (dominantAction == PlayerActions::JUMP || dominantAction == PlayerActions::ATTACK_3) {
        // If the animation is not done, progress
        if (currentSpriteFrame < spriteSheets[dominantAction].frameCount - 1)
            currentSpriteFrame++;
        // If it is done, remove the action
        else {
            currentActions.remove(dominantAction);
        }
    }

    // Set the new sprite frame
    setPixmap(
        spriteSheets[dominantAction].pixmap.copy(
            currentSpriteFrame * spriteSheets[dominantAction].frameWidth,
            0,
            spriteSheets[dominantAction].frameWidth,
            spriteSheets[dominantAction].frameHeight
            )
        );
}

void Player::handleWalking() {
    // Play Walking sound
    walkSound->play();
    // Start timer to handle horizontal movement
    horizontalMovementTimer->start(16);
}

void Player::stopWalking() {
    // Stop walking sound
    walkSound->stop();
    // Stop the horizontal movement timer
    horizontalMovementTimer->stop();
    // Remove the walking action
    currentActions.remove(WALK);
    // Update the sprite sheet
    setCurrentSprite();
}

void Player::handleHorizontalMovement() {

    // Do not move if the player is jumping
    if (currentActions.contains(JUMP))
        return;

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
    if (checkSceneBoundries(shift)) {
        setPos(x() + shift, y());
        emit playerPositionChanged();
    } else
        stopWalking();
}

void Player::handleJumping(bool moveHorizontally) {
    currentActions.insert(JUMP);
    verticalVelocity = jumpVelocity; // Set the initial jump speed
    // disconnect timer and start it again
    jumpTimer->disconnect();
    jumpTimer->connect(jumpTimer, &QTimer::timeout, this, [=](){
        updateJump(moveHorizontally);
    });
    jumpTimer->start(16);
}

void Player::updateJump(bool moveHorizontally) {
    // Update the player's vertical velocity (gravity effect)
    verticalVelocity += gravity;

    // Move the player by the current vertical velocity
    setY(y() + verticalVelocity);

    // Move the player horizontally if needed
    if (moveHorizontally) {
        setX(x() + direction * 3);
        emit playerPositionChanged();
    }

    // Stop the jump when the player lands (y position >= ground level)
    // Assuming ground; level is y = 300 (adjust as needed)
    if (y() >= game->height() * 0.88 - boundingRect().height()) {
        setY(game->height() * 0.88 - boundingRect().height());              // Reset to ground level
        currentActions.remove(JUMP);
        jumpTimer->stop();      // Stop the jump timer
        verticalVelocity = 0;   // Reset the velocity
        setCurrentSprite();
    }
}

void Player::handleAttack() {

}

void Player::changeDirection(PlayerDirections newDirection) {
    // If the player is already facing the new direction, do nothing
    if (direction == newDirection)
        return;

    // Change the direction of the player
    setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0), true);
    direction = newDirection;
}

bool Player::checkSceneBoundries(int dx) {
    int newXPosition = x() + dx;
    if (newXPosition - sceneOffset < 0 || newXPosition + sceneOffset > game->scene->width() - boundingRect().width())
        return false;
    return true;
}
