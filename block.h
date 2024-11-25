// Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include "qpainter.h"
#include <QGraphicsPixmapItem>

class Block : public QGraphicsPixmapItem {
public:
    Block(qreal x, qreal y, QString imagePath, qreal scale = 1.0);  // Add scale parameter with a default value

    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
    //     // Draw the pixmap
    //     QGraphicsPixmapItem::paint(painter, option, widget);

    //     // Draw the outline
    //     painter->setPen(QPen(Qt::red, 3)); // Change color and thickness as needed
    //     painter->drawRect(boundingRect());
    // }
};

#endif // BLOCK_H
