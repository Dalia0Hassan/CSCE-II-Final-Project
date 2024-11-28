#include "life.h"
#include <QGridLayout>
#include <QPixmap>

life::life(State* state, QWidget* parent)
    : QWidget(parent), state(state) {

    // Load the heart images
    fullHeart.load(":/Assets/images/full_heart.png");
    halfHeart.load(":/Assets/images/half_heart.png");
    emptyHeart.load(":/Assets/images/empty_heart.png");

    layout = new QGridLayout(this);

    // Initialize the heart display with ful hearts
    for (int i = 0; i < 5; ++i) {
        hearts[i] = new QLabel(this);
        hearts[i]->setPixmap(fullHeart);
        layout->addWidget(hearts[i], 0, i);  // Arrange hearts in a row
    }

    // Connect the stateChanged signal to update the heart display
    connect(state, &State::stateChanged, this, &life::updateLives);
}

void life::updateLives() {
    float lives = state->getLives(); // between 1.0 and 5.0 (the 0.5 stands for half a life)
    // lives =0 will be "game over"
    // Determine the number of full, half, and empty hearts
    int fullHearts = static_cast<int>(lives); // integer part represents the full hearts
    int halfHearts = (lives - fullHearts >= 0.5) ? 1 : 0; // Half heart if fractional part >= 0.5
    // int emptyHearts = 5 - fullHearts - halfHearts; // Remaining hearts are empty (the lost ones of the 5)

    // Update the display (loop over the hearts)
    for (int i = 0; i < 5; ++i) {
        if (i < fullHearts) { // show full hearts at the beginning
            hearts[i]->setPixmap(fullHeart);
        } else if (i < fullHearts + halfHearts) { // followed by the halfs
            hearts[i]->setPixmap(halfHeart);
        } else {
            hearts[i]->setPixmap(emptyHeart);
        }
    }
}
/*ex: lives = 3.5
full hearts = 3
half hearts = 1
empty h = 1

loop
i=0
shows the 3 full one (until i =2)
i=3
shows one half
after the it just fills the remaining positions with empty hearts
*/
