// Trap.cpp
#include "trap.h"
#include <QPixmap>

Trap::Trap(qreal x, qreal y, QString imagePath, qreal scale) {
    QPixmap trapImage(imagePath);

    // Check if the image loaded successfully
    if (trapImage.isNull()) {
        qDebug() << "Error loading image:" << imagePath;
    } else {
        // Scale the image using the provided scale factor
        trapImage = trapImage.scaled(trapImage.size() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        setPixmap(trapImage);  // Set the scaled pixmap
    }

    setPos(x, y);  // Set the position of the trap
    setFlag(QGraphicsItem::ItemIsFocusable);  // Make it focusable if needed
}