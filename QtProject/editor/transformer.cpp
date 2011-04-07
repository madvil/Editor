#include "transformer.h"

Transformer::Transformer(QObject *parent) : QObject(parent)
{
    assignedEntity = 0;
    redPen = QPen(QColor(255, 0, 0));
}

void Transformer::paint(QPainter *painter, QPaintEvent *event, int sliding)
{
    if (assignedEntity != 0) {
        painter->save();
        painter->setPen(redPen);

//        painter->scale(assignedEntity->getScaleX() + 0.1, assignedEntity->getScaleY() + 0.1);
        painter->rotate(assignedEntity->getAngle());
        painter->drawRect(assignedEntity->getPosX() - 2, assignedEntity->getPosY() - 2,
                          assignedEntity->getWidth() + 4, assignedEntity->getHeight() + 4);

        painter->restore();
    }
}

void Transformer::assignTo(Entity *entity)
{
    assignedEntity = entity;
}
