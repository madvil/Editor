#include "mover.h"
#include "scene.h"
#include "constants.h"

#define SIDE 4

Mover::Mover(QtAbstractPropertyBrowser *propertyBrowser) : Movable(propertyBrowser)
{
    visInTree = false;
    setRootName(LANDSCAPE_NAME);
    setName(FRACTURE_NAME);
    init();

    rootProperty->removeSubProperty(name);
    rootProperty->removeSubProperty(posZ);
    rootProperty->removeSubProperty(angle);
    rootProperty->removeSubProperty(width);
    rootProperty->removeSubProperty(height);

    darkRed = QBrush(QColor(100, 0, 0));
    green = QPen(QColor(0, 255, 0));
    red = QPen(QColor(255, 0, 0));

    width->setEnabled(false);
    height->setEnabled(false);
}

void Mover::paint(QPainter *painter, QPaintEvent *event, Scene *scene)
{
    QBrush brush = painter->brush();
    QPen pen = painter->pen();

    float ratio = scene->getRatio();
    int x = getPosX() * ratio;
    int y = scene->convertWorldCoordToWindow(getPosY());

    if (isSelected()) {
        painter->setPen(red);
    } else {
        painter->setPen(green);
    }

    painter->setBrush(darkRed);
    painter->drawRect(x - SIDE / 2, y - SIDE / 2, SIDE, SIDE);

    painter->setPen(pen);
    painter->setBrush(brush);
}

bool Mover::check(int w_x, int w_y, Scene *scene)
{
    bool ret = false;
    float ratio = scene->getRatio();
    int x = getPosX() * ratio;
    int y = scene->convertWorldCoordToWindow(getPosY());
    if (w_x + scene->getSlide() >= x - SIDE / 2 && w_x + scene->getSlide() <= x + SIDE / 2) {
        if (w_y >= y - SIDE / 2 && w_y <= y + SIDE / 2) {
            ret = true;
        }
    }

    return ret;
}
