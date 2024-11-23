// Block.cpp
#include "block.h"
#include <QPixmap>

Block::Block(qreal x, qreal y,  QString imagePath, qreal scale) {
    QPixmap blockImage(imagePath);

    // Check if the image loaded successfully
    if (blockImage.isNull()) {
        qDebug() << "Error loading image:" << imagePath;
    } else {
        // Scale the image using the provided scale factor
        blockImage = blockImage.scaled(blockImage.size() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        setPixmap(blockImage);  // Set the scaled pixmap
    }

    setPos(x, y);  // Set the position of the block
    setFlag(QGraphicsItem::ItemIsFocusable);  // Make it focusable if needed
}
