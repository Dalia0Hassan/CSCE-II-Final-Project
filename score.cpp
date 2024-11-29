#include "score.h"
#include <QFont>
#include <QGraphicsPixmapItem>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent) {
    // Initialize the score to 0
    scoreCount = 0;

    // Add the image to represent "Score:"
    QGraphicsPixmapItem* scoreImage = new QGraphicsPixmapItem(QPixmap(":/Assets/images/scoretext.png"));
    scoreImage->setParentItem(this); // Attach it as a child *parent is score* (to keep them grouped) this makes its postion "relative" to the score text
    scoreImage->setPos(-50, -5);     // Position the image relative to the score value

    // Set the initial score display
    setPlainText(QString::number(scoreCount));
    setDefaultTextColor(Qt::black);// set color
    setFont(QFont("Impact", 30));  // set font
    setPos(50, 0); // set the position of the score value

}

void Score::increase() {
    // Increment the score and update the display
    scoreCount++; // counts the number of increase attempts (to increase by a larger amount each time)
    setPlainText(QString::number(scoreCount * 15));  // increases the count by multiples of 15
}
void Score::big_increase() { // for stronger enemies

    scoreCount++; // counts the number of increase attempts (to increase by a larger amount each time)
    setPlainText(QString::number(scoreCount * 25));  // increases the count by multiples of 25
}
void Score::decrease() {
    // decrement the score and update the display

    scoreCount--;
    setPlainText(QString::number(scoreCount * 15));  // decreases the count by multiples of 15
}

void Score::big_decrease() {
    // decrement the score and update the display

    scoreCount--;
    setPlainText(QString::number(scoreCount * 25));  // decreases the count by multiples of 25
}


int Score::getScore() {
    return scoreCount;
}
