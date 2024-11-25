// Trap.h
#ifndef TRAP_H
#define TRAP_H

#include "qpainter.h"
#include "qpen.h"
#include <QGraphicsPixmapItem>

class Trap : public QGraphicsPixmapItem {
public:
    Trap(qreal x, qreal y, QString imagePath, qreal scale = 1.0);  // Add scale parameter with a default value

    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
    //     // Draw the pixmap
    //     QGraphicsPixmapItem::paint(painter, option, widget);

    //     // Draw the outline
    //     painter->setPen(QPen(Qt::red, 3)); // Change color and thickness as needed
    //     painter->drawRect(boundingRect());
    // }
};

#endif // TRAP_H
