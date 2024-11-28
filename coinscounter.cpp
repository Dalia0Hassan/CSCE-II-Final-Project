#include "coinscounter.h"
#include <QFont>
#include <QGraphicsPixmapItem>

coinsCounter::coinsCounter(QGraphicsItem * parent) : QGraphicsTextItem(parent) {
    // Initialize the coins to 0
    coinsCount=0;

    // Add the coin icon
    QGraphicsPixmapItem* coinImage = new QGraphicsPixmapItem(QPixmap(":/Assets/images/coin.png"));
    coinImage->setParentItem(this); // Attach it as a child (to keep them grouped) *position is set relatively*
    coinImage->setPos(-50, -5);     // Position the image relative to the coins count text

    // Set the initial coins count display
    setPlainText(QString::number(coinsCount));
    setDefaultTextColor(Qt::black);// set color
    setFont(QFont("Impact", 30));  // set font
    setPos(20, 0);                  // set the position of the text

}

void coinsCounter:: increaseCoins(int val ){

    setPlainText(QString::number(coinsCount+= val));  // increases the count by value sent


}

void coinsCounter:: decreaseCoins(int val ){

    setPlainText(QString::number(coinsCount-= val));  // decreases the count by value sent

}



int coinsCounter::  getCoins_Count(){
    return coinsCount;
}
