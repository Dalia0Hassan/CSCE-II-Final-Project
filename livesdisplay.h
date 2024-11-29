#ifndef LIVESDISPLAY_H
#define LIVESDISPLAY_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "State.h"
class livesDisplay:  public QObject, public QGraphicsItem
{    Q_OBJECT

    Q_INTERFACES(QGraphicsItem)

public:
        // Constructor
   livesDisplay(State* State, QGraphicsItem* parent = 0);
    // destructor
    // ~livesDisplay();

public slots:
    void updateLives();
private:
    static const int NumOfLives=5;
    State* state;                  // The player's state (lives)
    QGraphicsPixmapItem* hearts[NumOfLives];             // Array of QLabel to display hearts
    QPixmap  fullHeart;             // Image for a full heart
    QPixmap  halfHeart;             // Image for a half heart
    QPixmap  emptyHeart;            // Image for an empty heart
    float lives;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;


};

#endif // LIVESDISPLAY_H
