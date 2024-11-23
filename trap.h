// Trap.h
#ifndef TRAP_H
#define TRAP_H

#include <QGraphicsPixmapItem>

class Trap : public QGraphicsPixmapItem {
public:
    Trap(qreal x, qreal y, QString imagePath, qreal scale = 1.0);  // Add scale parameter with a default value
};

#endif // TRAP_H