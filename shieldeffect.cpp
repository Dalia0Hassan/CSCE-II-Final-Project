#include "shieldeffect.h"
#include "game.h"
#include "qgraphicsitem.h"
#include "qpen.h"
#include <QGraphicsBlurEffect>

extern Game *game;

ShieldEffect::ShieldEffect(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent) {
    // Set the size and position relative to the player
    setRect(-4 * widthOffset, -2 * heightOffset, parent->boundingRect().width() + 8 * widthOffset, parent->boundingRect().height()  + 4 * heightOffset);  // Adjust to match player size
    // Add a radial gradient for a bright effect
    gradient.setCenter(35, 35);       // Center of the ellipse
    gradient.setFocalPoint(35, 35);   // Focal point for brightness
    gradient.setRadius(35);           // Gradient radius
    gradient.setColorAt(0.0, QColor(0, 255, 255, 200));  // Bright core (cyan)
    gradient.setColorAt(1.0, QColor(0, 0, 255, 50));     // Faded edge (blue)

    // Create a radial gradient with a sky-blue glow
    QRadialGradient gradient(35, 35, 35);  // Center and radius
    gradient.setColorAt(0.0, QColor(135, 206, 250, 220));  // Core: Opaque sky blue
    gradient.setColorAt(1.0, QColor(135, 206, 250, 150));  // Edge: Semi-opaque sky blue

    setBrush(QBrush(gradient));  // Apply the gradient as the shield's brush
    setPen(Qt::NoPen);           // Remove the outline for a smooth appearance

    // Add a blur effect to make the glow soft and bright
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(10);  // Adjust for the desired glow intensity
    setGraphicsEffect(blurEffect);

}

void ShieldEffect::advance(int phase)  {
    if (!phase) return;
    // Update the position to follow the player
    setPos(parentItem()->pos());
}

ShieldEffect::~ShieldEffect() {
}
