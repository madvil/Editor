#include "transformer.h"

Transformer::Transformer(QObject *parent) : QObject(parent)
{

}

void Transformer::assignTo(Entity *entity)
{
    assignedEntity = entity;
}
