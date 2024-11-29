#include "livesdisplay.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
//#include "qgraphicsscene.h"
#include "settingsmanager.h"
livesDisplay::livesDisplay(State* state, QGraphicsItem* parent)
    : QGraphicsItem(parent), state(state) {


    // Heart Images
    fullHeart = QPixmap(SM.settings->value("window/lifeDisplayerImage1").toString()).scaled(30, 30);
    halfHeart = QPixmap(SM.settings->value("window/lifeDisplayerImage2").toString()).scaled(30, 30);
    emptyHeart = QPixmap(SM.settings->value("window/lifeDisplayerImage3").toString()).scaled(30, 30);



    // Create QGraphicsPixmapItem for each heart and add them to the scene
    for (int i = 0; i < NumOfLives; ++i) {
        hearts[i] = new QGraphicsPixmapItem();
            //hearts[i]->setPos()
        hearts[i]->setParentItem(this); //Attach them as a child (to keep them grouped) *position is set relatively*
        // Add the heart item to the scene
    }

    updateLives();

}
// livesDisplay::~livesDisplay(){
//         // Clean up dynamically allocated QLabel objects
//         for (int i = 0; i < 5; ++i) {
//             delete hearts[i];
//         }
// }

void livesDisplay::updateLives() {
    // Update lives based on current state
    lives = state->getLives(); // between 1.0 and 5.0 (the 0.5 stands for half a life)
    // lives =0 will be "game over"

    // Determine the number of full, half, and empty hearts
    int fullHearts = static_cast<int>(lives); // integer part represents the full hearts
    int halfHearts = (lives - fullHearts >= 0.5) ? 1 : 0; // Half heart if fractional part >= 0.5
    // int emptyHearts = 5 - fullHearts - halfHearts; // Remaining hearts are empty (the lost ones of the 5)

    // Update the display (loop over the hearts)
    for (int i = 0; i < NumOfLives; ++i) {
        if (i < fullHearts) { // show full hearts at the beginning
            hearts[i]->setPixmap(fullHeart);
        } else if (i < fullHearts + halfHearts) { // followed by the halfs
            hearts[i]->setPixmap(halfHeart);
        } else {
            hearts[i]->setPixmap(emptyHeart);
        }
        // Position the hearts in a row
        hearts[i]->setPos(i * (fullHeart.width() + 5), 0);
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


QRectF livesDisplay::boundingRect() const  {
    // returns the bounding rect
    return QRectF(0, 0, 150, 50);
}
void livesDisplay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    // No custom painting needed; all visual elements are handled by QGraphicsPixmapItem.
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
