#include "transformer.h"
#include "scene.h"

Transformer::Transformer(QObject *parent) : QObject(parent)
{
    scene = (Scene *)parent;
    assignedEntity = 0;
    redPen = QPen(QColor(255, 0, 0));
    whitePen = QPen(QColor(255, 255, 255));
}

void Transformer::paint(QPainter *painter, QPaintEvent *event, bool drawResizeRect, bool drawSize)
{
    if (assignedEntity != 0) {
        painter->save();

        float r = scene->getRatio();
        int x = assignedEntity->getPosX() * r;
        int y = scene->convertWorldCoordToWindow(assignedEntity->getPosY());
        int w = assignedEntity->getWidth() * r;
        int h = assignedEntity->getHeight() * r;

        painter->rotate(assignedEntity->getAngle());

        painter->setPen(whitePen);
        painter->drawText(x, y - 4, "x:" + QString::number(assignedEntity->getPosX()) + "; y:" +
                          QString::number(assignedEntity->getPosY()));

        if (drawSize)
            painter->drawText(x, y + h + 13, "w:" + QString::number(assignedEntity->getWidth()) + "; h:" +
                          QString::number(assignedEntity->getHeight()));

        painter->setPen(redPen);
        painter->drawRect(x, y, w, h);

        if (drawResizeRect)
            painter->drawRect(x + w - 10, y + h - 10, 10, 10);

        painter->restore();
    }
}

void Transformer::assignTo(Entity *entity)
{
    assignedEntity = entity;
}
