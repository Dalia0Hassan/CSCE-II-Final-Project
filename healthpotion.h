#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include <QObject>
#include <QGraphicsPixmapItem>

class HealthPotion :public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    HealthPotion( qreal x , qreal y , qreal scale ,QString path);

};

#endif // HEALTHPOTION_H
