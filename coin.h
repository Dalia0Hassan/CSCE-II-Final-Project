#ifndef COIN_H
#define COIN_H
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "player.h"
#include "settingsmanager.h"
#include "sound.h"
#include "utils.h"


class  Coin :  public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
private:
    qreal value;
    Sound *coinSound;
    QTimer *timer;
    static QStringList soundPaths;
    static qreal volume;
    // Helper functions
    void setRandomSound();

public:
    Coin( qreal x , qreal y , qreal scale , qreal value);
    qreal getValue() const;
    ~Coin() override;

public slots:
    void handleCollision();



};

#endif // COIN_H
