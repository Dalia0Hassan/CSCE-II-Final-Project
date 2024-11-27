// Trap.h
#ifndef TRAP_H
#define TRAP_H

#include "utils.h"
#include <QGraphicsPixmapItem>

class Trap : public QGraphicsPixmapItem {
public:
    Trap(qreal x, qreal y, QString imagePath, qreal scale = 1.0);  // Add scale parameter with a default value
    int type() const override {return TrapType;}
};

#endif // TRAP_H
