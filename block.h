// Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>

class Block : public QGraphicsPixmapItem {
public:
    Block(qreal x, qreal y, QString imagePath, qreal scale = 1.0);  // Add scale parameter with a default value
};

#endif // BLOCK_H