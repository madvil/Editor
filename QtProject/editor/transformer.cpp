#include "transformer.h"

Transformer::Transformer(QObject *parent) : QObject(parent) {

}

void Transformer::paint(QPainter *painter, QPaintEvent *event) {
    painter->save();

    painter->restore();
}

void Transformer::assignTo(Entity *entity) {
    assignedEntity = entity;
}
