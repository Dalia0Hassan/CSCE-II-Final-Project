#ifndef LIFEDISPLAY_H
#define LIFEDISPLAY_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include "State.h"
class LifeDisplay: public QWidget
{
    Q_OBJECT


    public:
        LifeDisplay(State* State, QWidget* parent = nullptr);

    public slots:
        void updateLives();
    private:
        State* state;                  // The player's state (lives)
        QLabel* hearts[5];             // Array of QLabel to display hearts
        int MaxNumOfLives =5;
        QPixmap fullHeart;             // Image for a full heart
        QPixmap emptyHeart;            // Image for an empty heart
        QGridLayout* layout;           // Layout to arrange the hearts in a row
};

#endif // LIFEDISPLAY_H



