#include "coinsdisplay.h"
#include "settingsmanager.h"
#include <QFont>
#include <QGraphicsPixmapItem>

CoinsDisplay::CoinsDisplay(int initialValue, QGraphicsItem * parent) : QGraphicsTextItem(parent) {

    // Set initial value
    value = initialValue;

    // Font
    setFont(QFont(
        SM.settings->value("window/coinsDisplayerFont").toString(),
        SM.settings->value("window/coinsDisplayerFontSize").toInt()
    ));

    // Color
    setDefaultTextColor(Qt::black);


    // Display initial value
    updateText();


    // Coin Image //
    QGraphicsPixmapItem* coinImage = new QGraphicsPixmapItem(
        QPixmap(SM.settings->value("window/coinsDisplayerImage").toString()).scaled(30, 30)
        );

    // Attach it as a child (to keep them grouped) *position is set relatively*
    coinImage->setParentItem(this);

    // Position the image relative to the coins count text
    coinImage->setPos(
        -coinImage->pixmap().width() - 2,
        (boundingRect().height() / 2) - (coinImage->pixmap().height() / 2)
    );

}


// Setters
void CoinsDisplay::set(int newValue){
    value = newValue;
    updateText();
}
void CoinsDisplay::increase(int val )  {
    set( value + val);
}

void CoinsDisplay::decrease(int val ) {
    if ( value - val < 0)
        throw "Coins cannot be negative";
    set( value - val);
}

void CoinsDisplay::increment() {
    increase(1);
}

void CoinsDisplay::decrement() {
    decrease(1);
}

// Helpers
void CoinsDisplay::updateText() {
    setPlainText(QString::number(value));
}

// Destructor
CoinsDisplay::~CoinsDisplay() {
    delete coinImage;
}
