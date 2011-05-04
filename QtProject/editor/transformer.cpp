#include "transformer.h"
#include "scene.h"

Transformer::Transformer(QObject *parent) : QObject(parent)
{
    scene = (Scene *)parent;
    assignedMovable = 0;
    redPen = QPen(QColor(255, 0, 0));
    whitePen = QPen(QColor(255, 255, 255));
}

void Transformer::paint(QPainter *painter, QPaintEvent *event, bool drawResizeRect, bool drawSize)
{
    if (assignedMovable != 0) {
        painter->save();
        {
            float r = scene->getRatio();
            int x = assignedMovable->getPosX() * r;
            int y = scene->convertWorldCoordToWindow(assignedMovable->getPosY());
            int w = assignedMovable->getWidth() * r;
            int h = assignedMovable->getHeight() * r;

            painter->rotate(assignedMovable->getAngle());

            painter->setPen(whitePen);
            painter->drawText(x, y - 4, "x:" + QString::number(assignedMovable->getPosX()) + "; y:" +
                              QString::number(assignedMovable->getPosY()));

            if (drawSize)
                painter->drawText(x, y + h + 13, "w:" + QString::number(assignedMovable->getWidth()) + "; h:" +
                              QString::number(assignedMovable->getHeight()));

            painter->setPen(redPen);
            painter->drawRect(x, y, w, h);

            if (drawResizeRect)
                painter->drawRect(x + w - 10, y + h - 10, 10, 10);
        }
        painter->restore();
    }
}

void Transformer::assignTo(Movable *m)
{
    assignedMovable = m;
}
