#ifndef COINSCOUNTER_H
#define COINSCOUNTER_H
#include <QGraphicsTextItem>

class coinsCounter: public QGraphicsTextItem
{
public:
    coinsCounter(QGraphicsItem * parent=0);
    void increaseCoins(int);
    void decreaseCoins(int);
    int getCoins_Count();
private:
    int coinsCount;
};

#endif // COINSCOUNTER_H
