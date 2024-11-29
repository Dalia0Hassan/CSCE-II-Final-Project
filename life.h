#ifndef LIFE_H
#define LIFE_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include "State.h"
class life: public QWidget
{
    Q_OBJECT


    public:
        life(State* State, QWidget* parent = nullptr);

    public slots:
        void updateLives();
    private:
        State* state;                  // The player's state (lives)
        QLabel* hearts[5];             // Array of QLabel to display hearts
        QPixmap fullHeart;             // Image for a full heart
        QPixmap halfHeart;             // Image for a half heart
        QPixmap emptyHeart;            // Image for an empty heart
        QGridLayout* layout;           // Layout to arrange the hearts in a row
};

#endif // LIFE_H



